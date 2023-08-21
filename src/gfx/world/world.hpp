#pragma once

#include "../../common.hpp"
#include "../../state.hpp"
#include "../gfx.hpp"
#include "../shader.hpp"
#include "../texture.hpp"
#include "chunk.hpp"

struct World {
  size_t chunk_size;
  Shader *shader;
  TextureAtlas *texture_atlas;
  int n_chunks = 12;
  int seed;
  int MAX_HEIGHT = 256;

  World(size_t chunk_size, int seed) {
    srand(seed);

    this->chunk_size = chunk_size;

    this->init();
  }

  std::vector<Chunk *> chunks;
  void generate();
  void init();
  void render();
  bool chunk_too_far(Chunk &chunk);
  Chunk *create_chunk(glm::vec3 position);
};
