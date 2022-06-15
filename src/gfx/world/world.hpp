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

  World(size_t chunk_size) {
    this->chunk_size = chunk_size;
    this->shader = new Shader("res/shaders/basicTexture.vert",
                              "res/shaders/basicTexture.frag");

    this->texture_atlas = new TextureAtlas("res/textures.png");

    this->init();
  }

  std::vector<Chunk *> chunks;
  void generate();
  void init();
  void render();
  bool chunk_too_far(Chunk &chunk);
  Chunk *new_chunk(glm::vec3 position);
};
