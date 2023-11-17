#pragma once

#include "block.hpp"

struct Stone : Block {
  Stone() {
    name = "stone";
    solid = true;
  }
  glm::vec2 textureOffset(Direction direction) { return glm::vec2(2, 1); }
};
