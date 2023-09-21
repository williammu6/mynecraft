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
  Block block;
};

struct World {
  World(size_t chunk_size, int seed) {
    srand(seed);
    this->seed = seed;
    this->chunk_size = chunk_size;
    this->sky = new Sky();
    this->init();
  }
  size_t chunk_size;
  Shader *shader;
  Sky *sky;
  int n_chunks = 16;
  int version = 1;
  int seed;

  std::vector<OutOfBoundsBlock> out_bounds_blocks{};
  std::unordered_map<glm::ivec3, Chunk *> chunk_map;

  void init();
  void render();
  bool chunk_too_far(Chunk &chunk);
  Chunk *get_chunk_at(int x, int z);
  void put_blocks_outta_bounds(Chunk *chunk);
};

#endif
