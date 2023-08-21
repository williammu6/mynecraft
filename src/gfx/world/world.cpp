#include "world.hpp"
#include "tree.hpp"

#include "../../blocks/blocks.hpp"
#include "../../utils/math.hpp"
#include "glm/common.hpp"
#include "perlin_noise.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>

void gen(Chunk *chunk, int chunkX, int chunkZ) {
  int CHUNK_SIZE = chunk->size;
  BlockType *block_type = nullptr;

  chunk->init();

  const siv::PerlinNoise::seed_type seed = 2u;
  const siv::PerlinNoise perlin{seed};

  for (int x = 0; x < CHUNK_SIZE; x++) {
    int nX = (x + 1) + chunkX * CHUNK_SIZE;
    for (int z = 0; z < CHUNK_SIZE; z++) {
      int nZ = (z + 1) + chunkZ * CHUNK_SIZE;
      const double noise = perlin.octave2D_01(nX * 0.01, nZ * 0.01, 4);
      int height = glm::max(1, (int)(noise * 64));

      if (height < 10) {
        block_type = new Water();
      } else if (height < 14) {
        block_type = new Sand();
      } else if (height < 96) {
        block_type = new Grass();
      } else {
        block_type = new Snow();
      }

      for (int y = 0; y < height; y++) {
        chunk->blocks[x][z].push_back({block_type, glm::vec3(x, y, z)});
      }

      for (int y = height; y < 64; y++) {
        chunk->blocks[x][z].push_back({new Air(), glm::vec3(x, y, z)});
      }

      if (RANDCHANCE(0.02) && strcmp(block_type->name, "sand") == 0) {
        for (int cY = height; cY < height + RAND(3, 5); cY++) {
          glm::vec3 cactus_position = {x, cY, z};
          // chunk->set(cactus_position, {new Cactus(), cactus_position});
        }
      }

      if (RANDCHANCE(0.01) && strcmp(block_type->name, "grass") == 0) {
        // create_tree({x, height, z}, chunk);
      }
    }
  }

  chunk->prepare_render();
}

Chunk *World::create_chunk(glm::vec3 position) {
  Chunk *chunk = new Chunk(position);
  gen(chunk, position.x, position.z);
  return chunk;
}

void World::init() {
  for (int i = 0; i < n_chunks; i++)
    for (int j = 0; j < n_chunks; j++)
      this->chunks.push_back(create_chunk(glm::vec3(i, 0, j)));

  glm::vec3 center = chunks[chunks.size() - 1]->position * 16.0f * 0.5f;
  state.camera.position = glm::vec3(center.x, 40, center.z);
}

void World::render() {
  for (int i = 0; i < chunks.size(); i++) {
    break;
    Chunk *chunk = chunks[i];

    auto xyChunk = glm::vec3(chunk->position.x, 0, chunk->position.z);
    auto xyCamera =
        glm::vec3(state.camera.position.x, 0, state.camera.position.z);

    float distance = (float)n_chunks * chunk->size / 2;
    float tooFar = distance * 4;

    float distanceX =
        chunk->position.x * (float)chunk->size - state.camera.position.x;
    float distanceZ =
        chunk->position.z * (float)chunk->size - state.camera.position.z;

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
      chunks.erase(chunks.begin() + i);
      Chunk *new_chunk = create_chunk(new_chunk_position);
      chunks.push_back(new_chunk);
      i--;
    }
  }

  for (Chunk *chunk : chunks)
    chunk->render();
}
