#pragma once

#include "shader.hpp"
#include "texture.hpp"

struct Renderer {
  Shader *shader;
  Shader *sun_shader;
  std::map<TextureID, Texture> textures;

  Renderer() {
    this->textures[TextureID::ATLAS] = texture_from_path("res/textures.png");
    this->textures[TextureID::SUN] = texture_from_path("res/sun.png");

    this->shader = new Shader("res/shaders/basicTexture.vert",
                              "res/shaders/basicTexture.frag");
    this->sun_shader =
        new Shader("res/shaders/sun.vert", "res/shaders/sun.frag");
  }
};
