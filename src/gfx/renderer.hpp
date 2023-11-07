#pragma once

#include "shader.hpp"
#include "texture.hpp"

// TODO delete this
struct Renderer {
  BlockShader *block_shader;
  CrosshairShader *crosshair_shader;
  SkyShader *sky_shader;
  std::map<TextureID, Texture> textures;

  Renderer() {
    this->textures[TextureID::ATLAS] = texture_from_path("res/textures.png");
    this->textures[TextureID::SUN] = texture_from_path("res/sun.png");
    this->textures[TextureID::CROSSHAIR] = texture_from_path("res/crosshair.png");

    this->block_shader = new BlockShader();
    this->crosshair_shader = new CrosshairShader();
    // this->sun_shader = new Shader("res/shaders/sun.vert", "res/shaders/sun.frag");
  }
};
