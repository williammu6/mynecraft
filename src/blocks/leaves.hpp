#pragma once

#include "block_type.hpp"

struct Leaves : BlockType {
  Leaves() {
    name = "wood";
    solid = true;
  }
  glm::vec2 texture_offset(Face face) {
    return glm::vec2(5, 0);
  }
};
