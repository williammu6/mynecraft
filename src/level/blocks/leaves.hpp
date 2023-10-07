#pragma once

#include "block.hpp"

struct Leaves : Block {
  Leaves() {
    name = "leaves";
    solid = true;
    transparent = true;
  }
  glm::vec2 textureOffset(Direction direction) {
    return glm::vec2(5, 0);
  }
};
