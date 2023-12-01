#ifndef RENDERER_H
#define RENDERER_H

#include "shader.hpp"
#include "texture.hpp"

struct Renderer {
  std::map<TextureID, Texture> textures;
  std::map<Shaders, Shader *> shaders;

  Renderer() {
    textures[TextureID::ATLAS] = textureFromPath("assets/textures/atlas.png");
    textures[TextureID::CROSSHAIR] =
        textureFromPath("assets/textures/crosshair.png");

    shaders[Shaders::CROSSHAIR] = new CrosshairShader();
    shaders[Shaders::BLOCK] = new BlockShader();
    shaders[Shaders::BLOCK_OUTLINE] = new BlockOutlineShader();
  }
};

#endif
