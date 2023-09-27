#pragma once

#include "block.hpp"

struct Cobblestone : Block {
  Cobblestone() {
    name = "cobblestone";
    solid = true;
  }
  glm::vec2 texture_offset(Direction face) { return glm::vec2(2, 0); }
};
