#include "world.hpp"

#include "../../block_type/air.hpp"
#include "../../block_type/block_type.hpp"
#include "../../block_type/cobblestone.hpp"
#include "../../block_type/grass.hpp"
#include "../../block_type/stone.hpp"
#include "../../block_type/water.hpp"
#include <cstdlib>

BlockType *block_types[] = {
    new Cobblestone(),
    new Stone(),
    new Grass(),
};

void gen(Chunk *chunk) {
  int CHUNK_SIZE = chunk->size;
  BlockType *block_type = nullptr;

  chunk->init();

  for (int x = 0; x < CHUNK_SIZE; x++) {
    block_type = block_types[(int)(rand() % 3)];
    for (int y = 0; y < CHUNK_SIZE; y++) {
      for (int z = 0; z < CHUNK_SIZE; z++) {
        /*
        int height = (int)((rand() + CHUNK_SIZE / 2) % CHUNK_SIZE);
        for (int y = 0; y < height; y++) {
          chunk->blocks[x][y].push_back({block_type, glm::vec3(x, y, z)});
        }
        for (int y = height; y < CHUNK_SIZE; y++) {
          chunk->blocks[x][y].push_back({new Air(), glm::vec3(x, y, z)});
        }
        */
        chunk->blocks[x][y].push_back({block_type, glm::vec3(x, y, z)});
      }
    }
  }

  chunk->prepare_render();
}

Chunk *World::new_chunk(glm::vec3 position) {
  Chunk *chunk = new Chunk(this->shader, this->texture_atlas, position);
  gen(chunk);
  return chunk;
}

void World::init() {
  for (int x = 0; x < 4; x++) {
    for (int z = 0; z < 4; z++) {
      chunks.push_back(new_chunk(glm::vec3(x, 0, z)));
    }
  }

  glm::vec3 center = chunks[chunks.size() - 1]->position * 16.0f * 0.5f;
  state.camera.cameraPos = glm::vec3(center.x, 40, center.z);
}

void World::render() {
  for (int i = 0; i < chunks.size(); i++) {
    break;
    Chunk *chunk = chunks[i];

    glm::vec3 distance_from_camera =
        chunk->position * (float)chunk->size - state.camera.cameraPos;

    if (distance_from_camera.x <= 32 && distance_from_camera.x >= -32 &&
        distance_from_camera.z <= 32 && distance_from_camera.z >= -32) {
      continue;
    }

    int new_x = chunk->position.x;
    int new_z = chunk->position.z;

    if (distance_from_camera.x > 32) {
      new_x -= 4;
    }
    if (distance_from_camera.x < -32) {
      new_x += 4;
    }
    if (distance_from_camera.z > 32) {
      new_z -= 4;
    }
    if (distance_from_camera.z < -32) {
      new_z += 4;
    }

    glm::vec3 new_chunk_position = glm::vec3(new_x, 0, new_z);

    delete chunk;
    chunks.erase(chunks.begin() + i);
    Chunk *new_chunk = this->new_chunk(new_chunk_position);
    chunks.push_back(new_chunk);
    i--;
  }

  for (Chunk *chunk : chunks)
    chunk->render();
}
