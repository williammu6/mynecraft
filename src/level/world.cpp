#include "world.hpp"
#include "../utils/math.hpp"
#include "blocks/blocks.hpp"
#include "glm/common.hpp"

void World::tick() {
  prepare_new_chunks(1);
  render();
  load_and_unload_chunks();
}

void World::render() {
  for (const auto &[position, chunk] : chunk_map) {
    chunk->render();
  }
}

void World::prepare_new_chunks(unsigned int max_throttle) {
  for (int i = 0; i < chunks_need_update.size() && i < max_throttle; i++) {
    Chunk *chunk = chunks_need_update[i];
    chunk->update();
    for (const auto c : chunk->neighbors()) {
      c->update();
    }
    chunks_need_update.erase(chunks_need_update.begin() + i);
    i--;
  }
}

void World::load_and_unload_chunks() {
  auto it = chunk_map.begin();
  while (it != chunk_map.end()) {
    Chunk *chunk = it->second;
    auto xyChunk = glm::vec3(chunk->position.x, 0, chunk->position.z);
    auto xyCamera =
        glm::vec3(state.camera.position.x, 0, state.camera.position.z);

    float distance = (float)n_chunks * chunk->SIZE / 2;
    float tooFar = distance * 4;

    float distanceX =
        chunk->position.x * (float)chunk->SIZE - state.camera.position.x;
    float distanceZ =
        chunk->position.z * (float)chunk->SIZE - state.camera.position.z;

    if (distanceX <= distance && distanceX >= -distance &&
        distanceZ <= distance && distanceZ >= -distance) {
      it++;
      continue;
    }

    int newX = it->first.x;
    int newZ = it->first.z;

    if (distanceX > distance)
      newX -= n_chunks;
    if (distanceX < -distance)
      newX += n_chunks;
    if (distanceZ > distance)
      newZ -= n_chunks;
    if (distanceZ < -distance)
      newZ += n_chunks;

    if (newX != chunk->position.x || newZ != chunk->position.z) {
      delete chunk;
      chunk_map.erase(it++);
      Chunk *new_chunk = create_chunk(glm::vec3(newX, 0, newZ), this);
      chunk_map[{newX, 0, newZ}] = new_chunk;
      chunks_need_update.push_back(new_chunk);
      version++;
      break;
    } else {
      it++;
    }
  }
}

Chunk *World::get_chunk_at(int x, int z) {
  if (chunk_map.find({x, 0, z}) != chunk_map.end()) {
    return chunk_map.at({x, 0, z});
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
