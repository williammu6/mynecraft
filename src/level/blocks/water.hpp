#pragma once

#include "block.hpp"

struct Water : Block {
  Water() {
    name = "water";
    solid = false;
    transparent = false;
    liquid = true;
  }
  glm::vec2 texture_offset(Direction direction) { return glm::vec2(3, 0); }
};
