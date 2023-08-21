#pragma once

#include "block_type.hpp"

struct Sun : BlockType {
  Sun() {
    name = "Sun";
    solid = true;
  }
  glm::vec2 texture_offset(Face face) { return glm::vec2(0, 2); }
};
