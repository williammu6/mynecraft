#pragma once

#include "block.hpp"

struct Stone : Block {
  Stone() {
    name = "stone";
    solid = true;
  }
  glm::vec2 texture_offset(Direction direction) { return glm::vec2(2, 1); }
};
