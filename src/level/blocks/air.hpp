#pragma once

#include "block.hpp"

struct Air : Block {
  Air() {
    name = "air";
    solid = false;
  }
  glm::vec2 textureOffset(Direction direction) { return glm::vec2(2, 0); }
};
