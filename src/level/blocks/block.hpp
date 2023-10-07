#ifndef BLOCK_H
#define BLOCK_H

#include "../../gfx/direction.hpp"
#include "../../gfx/gfx.hpp"

enum class TextureRotation { DEGREES_0, DEGREES_90, DEGREES_180, DEGREES_270 };

struct Block {
  const char *name;
  bool solid = true;
  bool transparent = false;
  bool liquid = false;
  TextureRotation rotation = TextureRotation::DEGREES_0;

  ~Block(){};
  virtual glm::vec2 textureOffset(Direction direction) = 0;
  bool drawable() {
    return solid || liquid;
  }
};

#endif
