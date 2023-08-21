#pragma once

#include "gfx.hpp"
#include "vendor/stb_image.h"
#include <iostream>

unsigned int texture_from_path(const char *path);

struct TextureAtlas {
  unsigned int texture;

  int tW = 64;
  int tH = 64;

  int atlas_width = 512;
  int atlas_height = 512;

  TextureAtlas() = default;
  TextureAtlas(const char *path) { this->texture = texture_from_path(path); }
};
