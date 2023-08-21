#pragma once

#include "block_type.hpp"

struct Sand : BlockType {
  Sand() {
    name = "sand";
    solid = true;
  }
  glm::vec2 texture_offset(Face face) {
    return glm::vec2(4, 1);
  }
};