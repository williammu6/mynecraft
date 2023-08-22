#pragma once

#include "block_type.hpp"

struct Snow : BlockType {
  Snow() {
    name = "snow";
    solid = true;
  }
  glm::vec2 texture_offset(Direction direction) {
    switch (direction) {
    case WEST:
    case EAST:
    case NORTH:
    case SOUTH:
      return glm::vec2(6, 1);
    case TOP:
      return glm::vec2(5, 1);
    case DOWN:
      return glm::vec2(0, 0);
    }
  }
};
