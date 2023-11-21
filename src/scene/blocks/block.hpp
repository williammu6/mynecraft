#ifndef BLOCK_H
#define BLOCK_H

#include "../../gfx/direction.hpp"
#include "../../gfx/gfx.hpp"
#include "../../physics/aabb.hpp"

enum class TextureRotation { DEGREES_0, DEGREES_90, DEGREES_180, DEGREES_270 };

struct Block {
  const char *name;
  bool solid = true;
  bool transparent = false;
  bool liquid = false;
  bool rendered = false;
  TextureRotation rotation = TextureRotation::DEGREES_0;
  static constexpr AABB aabb = {.min = glm::vec3(0.0f), .max = glm::vec3(1.0f)};

  ~Block(){};
  virtual glm::vec2 textureOffset(Direction direction) = 0;
  bool drawable() {
    return solid || liquid;
  }
};

#endif
