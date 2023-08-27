#pragma once

#include "gfx.hpp"
#include "vendor/stb_image.h"
#include "../common.hpp"

enum class TextureID {
  ATLAS = 0,
  SUN
};

struct Texture {
  GLuint texture;
  int tile_size = 64;
  int width;
  int height;
};

Texture texture_from_path(const char *path);
