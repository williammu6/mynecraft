#ifndef WORLD_H
#define WORLD_H

#include "../common.hpp"
#include "../gfx/gfx.hpp"
#include "../gfx/shader.hpp"
#include "../state.hpp"
#include "../utils/position.hpp"
#include "sky.hpp"
#include "chunk.hpp"

#define MAX_WORLD_HEIGHT = 256;

struct OutOfBoundsBlock {
  glm::ivec3 chunk_position;
  glm::ivec3 block_position;
  Block block;
};

struct World {
  size_t chunk_size;
  Shader *shader;
  Sky *sky;
  int n_chunks = 18;
  int version = 1;
  int seed;

  World(size_t chunk_size, int seed) {
    srand(seed);

    this->chunk_size = chunk_size;
    this->sky = new Sky();

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

#endif
