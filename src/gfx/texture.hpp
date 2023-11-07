#pragma once

#include "../common.hpp"
#include "gfx.hpp"
#include "vendor/stb_image.h"

enum class TextureID { ATLAS = 0, SUN, CROSSHAIR };

struct Texture {
  TextureID id;
  GLuint pixels;
  int tile_size = 64;
  int width;
  int height;
};

Texture texture_from_path(const char *path);
