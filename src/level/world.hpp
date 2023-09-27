#ifndef WORLD_H
#define WORLD_H

#include "../common.hpp"
#include "../gfx/gfx.hpp"
#include "../gfx/shader.hpp"
#include "../state.hpp"
#include "../utils/position.hpp"
#include "sky.hpp"
#include "chunk.hpp"

struct OutOfBoundsBlock {
  glm::ivec3 chunk_position;
  glm::ivec3 block_position;
  Block *block;
};

struct World {
  World(int seed) {
    srand(seed);
    this->seed = seed;
    for (int x = 0; x < n_chunks; x++) {
      for (int z = 0; z < n_chunks; z++) {
        Chunk *chunk = create_chunk(glm::ivec3(x, 0, z), this);
        this->chunk_map[{x, 0, z}] = chunk;
      }
    }

    for (const auto &[position, chunk] : chunk_map) {
      chunk->update();
    }

    glm::vec3 center =
      chunk_map[{n_chunks - 1, 0, n_chunks - 1}]->position * 16.0f * 0.5f;
    state.camera.position = glm::vec3(center.x, 40, center.z);
  }

  int n_chunks = 16;
  int version = 1;
  int seed;

  std::vector<OutOfBoundsBlock> out_bounds_blocks{};
  std::unordered_map<glm::ivec3, Chunk *> chunk_map;
  std::vector<Chunk*> chunks_need_update;

  void tick();
  void render();
  void load_and_unload_chunks();
  void prepare_new_chunks(unsigned int max_throttle);


  void put_pending_blocks(Chunk *chunk);

  Chunk *get_chunk_at(int x, int z);
};

#endif
