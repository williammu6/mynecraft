#pragma once

#include "block_type.hpp"

struct Cactus : BlockType {
  Cactus() {
    name = "cactus";
    solid = true;
  }
  glm::vec2 texture_offset(Direction direction) {
    if (direction == WEST || direction == EAST) {
      return glm::vec2(7, 0);
    }
    return glm::vec2(6, 0);
  }
};
