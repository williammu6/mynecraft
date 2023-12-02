#pragma once

#include "../common.hpp"
#include "../vendor/stb_image.h"
#include "gfx.hpp"

enum class TextureID { ATLAS = 0, SUN, CROSSHAIR };

struct Texture {
  TextureID id;
  GLuint pixels;
  int tileSize = 16;
  int width;
  int height;
};

Texture textureFromPath(const char *path);
Texture
cubemapTextureFromPath(const std::array<const std::string, 6> textureFaces);
