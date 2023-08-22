#pragma once

#include "block_type.hpp"

struct Wood : BlockType {
  Wood() {
    name = "wood";
    solid = true;
  }
  glm::vec2 texture_offset(Direction direction) {
    switch (direction) {
    case TOP:
    case DOWN:
      return glm::vec2(4, 0);
    case WEST:
    case EAST:
      return glm::vec2(3, 2);
    default:
      return glm::vec2(3, 1);
    }
  }
};
