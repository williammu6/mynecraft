#include "world.hpp"

#include "../../block_type/air.hpp"
#include "../../block_type/block_type.hpp"
#include "../../block_type/leaves.hpp"
#include "../../block_type/cobblestone.hpp"
#include "../../block_type/grass.hpp"
#include "../../block_type/stone.hpp"
#include "../../block_type/water.hpp"
#include "../../block_type/wood.hpp"
#include "../../block_type/cactus.hpp"
#include "../../block_type/sand.hpp"
#include "glm/common.hpp"
#include "perlin_noise.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>

BlockType *block_types[] = {
    new Cobblestone(),
    new Stone(),
    new Grass(),
};

void gen(Chunk *chunk, int chunkX, int chunkZ) {
  int CHUNK_SIZE = chunk->size;
  BlockType *block_type = nullptr;

  chunk->init();

  const siv::PerlinNoise::seed_type seed = 1u;
  const siv::PerlinNoise perlin{ seed };

  for (int x = 0; x < CHUNK_SIZE; x++) {
    int nX = (x + 1) + chunkX * CHUNK_SIZE;
    for (int z = 0; z < CHUNK_SIZE; z++) {
      int nZ = (z + 1) + chunkZ * CHUNK_SIZE;
      const double noise = perlin.octave2D_01(nX*0.01, nZ*0.01, 4); 
      int height = glm::max(1, (int)(noise * 64));

      block_type = new Air();

      if (height < 10) {
        block_type = new Water();
      } else if (height < 14) {
        block_type = new Sand();
      } else if (height < 20) {
        block_type = new Stone();
      } else {
        block_type = new Grass();
      }
      for (int y = 0; y < height; y++) {
        chunk->blocks[x][z].push_back({block_type, glm::vec3(x, y, z)});
      }

      std::cout << (float)(rand() / RAND_MAX) << std::endl;
      if ((float)(rand() / RAND_MAX) < 0.047 && block_type->name == "sand") {
        int cactusHeight = 3;
        for (int cactusY = height; cactusY < height + cactusHeight; cactusY++)
          chunk->blocks[x][z].push_back({new Cactus(), glm::vec3(x, cactusY, z)});
      }

      // for (int y = height; y < CHUNK_SIZE; y++) {
        // chunk->blocks[x][z].push_back({new Air(), glm::vec3(x, y, z)});
      // }


      continue;

      const double tree = perlin.octave2D_01(x*0.001, z*0.001, 4); 

      if (tree < 0.46 && block_type->name == "grass") {
        int tree_height = 5;
        int tree_top = height + tree_height;
        for (int y = height; y < tree_top; y++) {
          chunk->blocks[x][z].push_back({new Wood(), glm::vec3(x, y, z)});
        }
        continue;
        for (int xx = x - 5; xx < x + 5; xx++) {
          for (int zz = z - 5; zz < z + 5; zz++) {
            for (int yy = tree_top; yy < tree_top + 5; yy++) {
              chunk->blocks[x][z].push_back({new Leaves(), glm::vec3(xx, yy, zz)});
            }
          }
        }
      }
    }
  }

  chunk->prepare_render();
}

Chunk *World::create_chunk(glm::vec3 position) {
  Chunk *chunk = new Chunk(this->shader, this->texture_atlas, position);
  gen(chunk, position.x, position.z);
  return chunk;
}

void World::init() {
  for (int i = 0; i < n_chunks; i++)
    for (int j = 0; j < n_chunks; j++)
      this->chunks.push_back(create_chunk(glm::vec3(i, 0, j)));

  glm::vec3 center = chunks[chunks.size() - 1]->position * 16.0f * 0.5f;
  state.camera.cameraPos = glm::vec3(center.x, 40, center.z);
}

void World::render() {
  for (int i = 0; i < chunks.size(); i++) {
    Chunk *chunk = chunks[i];

    auto xyChunk = glm::vec3(chunk->position.x, 0, chunk->position.z);
    auto xyCamera = glm::vec3(state.camera.cameraPos.x, 0, state.camera.cameraPos.z);

    float distance = n_chunks * chunk->size / 2;
    float tooFar = distance*4;

    float distanceX = chunk->position.x * (float)chunk->size - state.camera.cameraPos.x;
    float distanceZ = chunk->position.z * (float)chunk->size - state.camera.cameraPos.z;


    if (distanceX <= distance && distanceX >= -distance &&
        distanceZ <= distance && distanceZ >= -distance) {
      continue;
    }

    int newX = chunk->position.x;
    int newZ = chunk->position.z;
    if (distanceX > distance) newX -= n_chunks;
    if (distanceX < -distance) newX += n_chunks;
    if (distanceZ > distance) newZ -= n_chunks;
    if (distanceZ < -distance) newZ += n_chunks;

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
