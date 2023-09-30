#include "world.hpp"
#include "../utils/math.hpp"
#include "blocks/blocks.hpp"
#include "chunk.hpp"
#include "glm/common.hpp"

void World::tick() {
  load_and_unload_chunks();
  prepare_new_chunks(1);
  render();
  delete_far_chunks();
}

float squared_distance(const glm::vec3 &a, const glm::vec3 &b) {
  glm::vec3 diff = b - a;
  return glm::dot(diff, diff);
}

bool sortByDistance(const glm::vec3 &a, const glm::vec3 &b,
                    const glm::vec3 &reference) {
  return squared_distance(a, reference) > squared_distance(b, reference);
}

glm::ivec3 get_current_chunk_position() {
  int currX = state.camera.position.x < 0 ? state.camera.position.x / 16 - 1
                                          : state.camera.position.x / 16;
  int currZ = state.camera.position.z < 0 ? state.camera.position.z / 16 - 1
                                          : state.camera.position.z / 16;
  return glm::ivec3(currX, 0, currZ);
}

void World::delete_far_chunks() {
  glm::ivec3 cc = get_current_chunk_position();
  auto it = chunks.begin();
  while (it != chunks.end()) {
    if (std::abs(it->first.x - cc.x) > n_chunks ||
        std::abs(it->first.z - cc.z) > n_chunks) {
      delete it->second;
      chunks.erase(it);
    }
    it++;
  }
}

void World::render() {
  glm::ivec3 cc = get_current_chunk_position();

  std::vector<glm::ivec3> positions;
  for (const auto &[position, _] : chunks) {
    positions.push_back(position);
  }

  std::sort(positions.begin(), positions.end(),
            [&](const glm::vec3 &a, const glm::vec3 &b) {
              return sortByDistance(a, b, cc);
            });

  for (const auto position : positions) {
    if (chunks.find(position) != chunks.end()) {
      chunks[position]->render();
    }
  }
}

void World::prepare_new_chunks(unsigned int max_throttle) {
  for (int i = 0; i < chunks_need_update.size() && i < max_throttle; i++) {
    Chunk *chunk = chunks_need_update[i];
    chunk->update();
    for (const auto c : chunk->neighbors()) {
      if (c->version != this->version)
        c->update();
    }
    chunks_need_update.erase(chunks_need_update.begin() + i);
    i--;
  }
}

void World::new_chunk_at(glm::ivec3 chunk_position) {
  Chunk *new_chunk = create_chunk(chunk_position, this);
  chunks[chunk_position] = new_chunk;
  chunks_need_update.push_back(new_chunk);
  version++;
}

void World::load_and_unload_chunks() {
  glm::ivec3 cc = get_current_chunk_position();
  for (int x = cc.x - n_chunks; x < cc.x + n_chunks; x++) {
    for (int z = cc.z - n_chunks; z < cc.z + n_chunks; z++) {
      auto new_chunk_position = glm::ivec3(x, 0, z);
      if (chunks.find(new_chunk_position) == chunks.end()) {
        new_chunk_at(new_chunk_position);
        return;
      }
    }
  }
}

Chunk *World::get_chunk_at(glm::ivec3 position) {
  if (chunks.find(position) != chunks.end()) {
    return chunks.at(position);
  }
  return nullptr;
}

void World::put_pending_blocks(Chunk *chunk) {
  for (int i = 0; i < out_bounds_blocks.size(); i++) {
    OutOfBoundsBlock outtabounds = out_bounds_blocks[i];
    if (outtabounds.chunk_position.x == chunk->position.x &&
        outtabounds.chunk_position.z == chunk->position.z) {
      chunk->set(outtabounds.block_position, outtabounds.block);
      out_bounds_blocks.erase(out_bounds_blocks.begin() + i);
    }
  }
}
