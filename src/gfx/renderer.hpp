#pragma once

#include "shader.hpp"
#include "texture.hpp"

struct Renderer {
  Shader *shader;
  std::map<TextureID, Texture> textures;

  Renderer() {
    this->textures[TextureID::SUN] = texture_from_path("res/sun.png");
    this->textures[TextureID::ATLAS] = texture_from_path("res/textures.png");

    this->shader = new Shader("res/shaders/basicTexture.vert",
                              "res/shaders/basicTexture.frag");
  }
};
