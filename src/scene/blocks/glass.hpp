#pragma once

#include "block.hpp"

struct Glass : Block {
  Glass() {
    name = "glass";
    solid = true;
    transparent = true;
  }
  glm::vec2 textureOffset(Direction direction) {
    return glm::vec2(7, 1);
  }
};
