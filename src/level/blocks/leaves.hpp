#pragma once

#include "block_type.hpp"

struct Leaves : BlockType {
  Leaves() {
    name = "leaves";
    solid = true;
    transparent = true;
  }
  glm::vec2 texture_offset(Direction direction) {
    return glm::vec2(5, 0);
  }
};
