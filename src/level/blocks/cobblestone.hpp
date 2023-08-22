#pragma once

#include "block_type.hpp"

struct Cobblestone : BlockType {
  Cobblestone() {
    name = "cobblestone";
    solid = true;
  }
  glm::vec2 texture_offset(Direction face) { return glm::vec2(2, 0); }
};
