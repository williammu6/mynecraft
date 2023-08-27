#pragma once

#include "../common.hpp"
#include "../gfx/gfx.hpp"
#include "../gfx/shader.hpp"
#include "../state.hpp"
#include "../utils/position.hpp"
#include "chunk.hpp"

struct OutOfBoundsBlock {
  glm::ivec3 chunk_position;
  glm::ivec3 block_position;
  Block block;
};

struct World {
  size_t chunk_size;
  Shader *shader;
  int n_chunks = 2;
  int version = 1;
  int seed;
  int MAX_HEIGHT = 256;

  World(size_t chunk_size, int seed) {
    srand(seed);

    this->chunk_size = chunk_size;

    this->init();
  }

  std::vector<OutOfBoundsBlock> out_bounds_blocks{};

  std::unordered_map<Position, Chunk *, Position::Hash> chunk_map;
  void init();
  void render();
  bool chunk_too_far(Chunk &chunk);
  Chunk *get_chunk_at(int x, int z);
  void put_blocks_outta_bounds(Chunk *chunk);
};
