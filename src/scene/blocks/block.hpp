#ifndef BLOCK_H
#define BLOCK_H

#include "../../gfx/cube_face.hpp"

enum class TextureRotation { DEGREES_0, DEGREES_90, DEGREES_180, DEGREES_270 };

struct Block {
  ~Block(){};
  TextureRotation rotation = TextureRotation::DEGREES_0;

  bool liquid = false;
  bool rendered = false;
  bool solid = true;
  bool transparent = false;
  const char *name;

  virtual glm::vec2 textureOffset(Direction direction) = 0;

  bool drawable() {
    return solid || liquid;
  }
};

#endif
