#pragma once

#include "shader.hpp"
#include "texture.hpp"

struct Renderer {
  TextureAtlas *texture_atlas;
  Shader *shader;
};
