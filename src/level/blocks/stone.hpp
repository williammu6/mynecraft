#pragma once

#include "block_type.hpp"

struct Stone : BlockType {
  Stone() {
    name = "stone";
    solid = true;
  }
  glm::vec2 texture_offset(Direction direction) { return glm::vec2(2, 1); }
};
