#pragma once

#include "block.hpp"

struct Sand : Block {
  Sand() {
    name = "sand";
    solid = true;
  }
  glm::vec2 textureOffset(Direction direction) {
    return glm::vec2(4, 1);
  }
};
