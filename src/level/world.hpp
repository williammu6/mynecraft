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
    glm::vec3 center(0.0f);
    state.camera.position = glm::vec3(center.x, 40, center.z);
  }

  int n_chunks = 16;
  int version = 1;
  int seed;

  std::vector<OutOfBoundsBlock> out_bounds_blocks{};
  std::unordered_map<glm::ivec3, Chunk *> chunks;
  std::vector<Chunk*> chunks_need_update;

  void tick();
  void render();
  void load_and_unload_chunks();
  void prepare_new_chunks(unsigned int max_throttle);
  void put_pending_blocks(Chunk *chunk);
  void new_chunk_at(glm::ivec3 chunk_position);
  void delete_far_chunks();
  Chunk *get_chunk_at(glm::ivec3 position);
  bool is_chunk_far(glm::ivec3 chunk_position);
};

#endif
