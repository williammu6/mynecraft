#pragma once

#include "block_type.hpp"

struct Water : BlockType {
  Water() {
    name = "water";
    solid = true;
  }
  glm::vec2 texture_offset(Face face) { return glm::vec2(3, 0); }
};
