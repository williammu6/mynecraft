#ifndef RENDERER_H
#define RENDERER_H

#include "shader.hpp"
#include "texture.hpp"

struct Renderer {
  std::map<TextureID, Texture> textures;
  std::map<Shaders, Shader *> shaders;

  Renderer() {
    textures[TextureID::ATLAS] = texture_from_path("res/textures.png");
    textures[TextureID::SUN] = texture_from_path("res/sun.png");
    textures[TextureID::CROSSHAIR] = texture_from_path("res/crosshair.png");

    shaders[Shaders::CROSSHAIR] = new CrosshairShader();
    shaders[Shaders::BLOCK] = new BlockShader();
    shaders[Shaders::RAY] = new RayShader();
    shaders[Shaders::BLOCK_OUTLINE] = new BlockOutlineShader();
  }
};

#endif
