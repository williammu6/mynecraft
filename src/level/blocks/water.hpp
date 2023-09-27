#pragma once

#include "block.hpp"

struct Water : Block {
  Water() {
    name = "water";
    solid = true;
    transparent = false;
  }
  glm::vec2 texture_offset(Direction direction) { return glm::vec2(3, 0); }
};
