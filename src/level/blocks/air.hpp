#pragma once

#include "block_type.hpp"

struct Air : BlockType {
  Air() {
    name = "air";
    solid = false;
  }
  glm::vec2 texture_offset(Direction direction) { return glm::vec2(2, 0); }
};
