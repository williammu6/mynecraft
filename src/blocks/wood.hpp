#pragma once

#include "block_type.hpp"

struct Wood : BlockType {
  Wood() {
    name = "wood";
    solid = true;
  }
  glm::vec2 texture_offset(Face face) {
    switch (face) {
    case TOP:
    case BOTTOM:
      return glm::vec2(4, 0);
    case LEFT:
    case RIGHT:
      return glm::vec2(3, 2);
    default:
      return glm::vec2(3, 1);
    }
  }
};
