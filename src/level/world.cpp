#include "world.hpp"

#include "../utils/math.hpp"
#include "blocks/blocks.hpp"
#include "glm/common.hpp"

void World::init() {
  for (int i = 0; i < n_chunks; i++)
    for (int j = 0; j < n_chunks; j++) {
      Chunk *chunk = create_chunk(glm::vec3(i, 0, j), this);
      this->chunks.push_back(chunk);
    }

  for (Chunk *chunk : this->chunks)
    chunk->prepare_render();

  glm::vec3 center = chunks[chunks.size() - 1]->position * 16.0f * 0.5f;
  state.camera.position = glm::vec3(center.x, 40, center.z);
}

void World::render() {
  for (int i = 0; i < chunks.size(); i++) {
    Chunk *chunk = chunks[i];

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
      continue;
    }

    int newX = chunk->position.x;
    int newZ = chunk->position.z;
    if (distanceX > distance)
      newX -= n_chunks;
    if (distanceX < -distance)
      newX += n_chunks;
    if (distanceZ > distance)
      newZ -= n_chunks;
    if (distanceZ < -distance)
      newZ += n_chunks;

    if (newX != chunk->position.x || newZ != chunk->position.z) {
      glm::vec3 new_chunk_position = glm::vec3(newX, 0, newZ);
      delete chunk;
      chunks[i] = create_chunk(new_chunk_position, this);
      chunks[i]->prepare_render();
    }
  }

  for (Chunk *chunk : chunks) {
    chunk->render();
  }
}

Chunk *World::get_chunk_at(int x, int z) {
  for (Chunk *chunk : this->chunks) {
    if (chunk->position.x == x && chunk->position.z == z)
      return chunk;
  }
  return nullptr;
}
