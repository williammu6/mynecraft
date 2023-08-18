#pragma once

#include "block_type.hpp"

struct Wood : BlockType {
  Wood() {
    name = "wood";
    solid = true;
  }
  glm::vec2 texture_offset(Face face) {
    if (face == TOP || face == BOTTOM) {
      return glm::vec2(4, 0);
    }
    return glm::vec2(3, 1);
  }
};
