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

float squared_distance(const glm::ivec3 &a, const glm::ivec3 &b) {
  glm::vec3 diff = b - a;
  return glm::dot(diff, diff);
}

bool sortByDistance(const glm::ivec3 &a, const glm::ivec3 &b,
                    const glm::ivec3 &reference) {
  return squared_distance(a, reference) > squared_distance(b, reference);
}

glm::ivec3 get_current_chunk_position() {
  int currX = state.camera.position.x < 0 ? state.camera.position.x / 16 - 1
                                          : state.camera.position.x / 16;
  int currZ = state.camera.position.z < 0 ? state.camera.position.z / 16 - 1
                                          : state.camera.position.z / 16;
  return glm::ivec3(currX, 0, currZ);
}

bool World::is_chunk_far(glm::ivec3 chunk_position) {
  glm::ivec3 cc = get_current_chunk_position();
  auto diff = chunk_position - cc;
  return std::abs(diff.x) > n_chunks || std::abs(diff.z) > n_chunks;
}

void World::delete_far_chunks() {
  auto it = chunks.begin();
  while (it != chunks.end()) {
    if (is_chunk_far(it->first)) {
      delete it->second;
      chunks.erase(it);
    }
    it++;
  }
}

/**
 * renders chunks from furthest to closer
 * so water transparency works correclty
 */
void World::render() {
  glm::ivec3 cc = get_current_chunk_position();

  std::vector<glm::ivec3> positions;
  for (const auto &[position, _] : chunks) {
    positions.push_back(position);
  }

  std::sort(positions.begin(), positions.end(),
            [&](const glm::ivec3 &a, const glm::ivec3 &b) {
              return sortByDistance(a, b, cc);
            });

  for (const auto position : positions) {
    chunks[position]->render();
  }
}

/**
 * update chunk mesh (vertices and indices)
 * this happens every time a chunk changes or one of its neighbors change
 * it is important so block faces between chunks aren't rendered
 */
void World::prepare_new_chunks(unsigned int max_throttle) {
  for (int i = 0; i < chunks_need_update.size() && max_throttle-- >= 0; i++) {
    Chunk *chunk = chunks_need_update[i];
    chunk->update();
    for (const auto neighbor_chunk : chunk->neighbors()) {
      neighbor_chunk->update();
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
  for (int i = 0; i < pending_blocks.size(); i++) {
    PendingBlock pending_block = pending_blocks[i];
    if (pending_block.chunk_position.x == chunk->position.x &&
        pending_block.chunk_position.z == chunk->position.z) {
      chunk->set(pending_block.block_position, pending_block.block);
      pending_blocks.erase(pending_blocks.begin() + i);
    }
  }
}
