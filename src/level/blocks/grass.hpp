#pragma once

#include "block_type.hpp"

struct Grass : BlockType {
  Grass() {
    name = "grass";
    solid = true;
  }
  glm::vec2 texture_offset(Direction direction) {
    switch (direction) {
    case DOWN:
      return glm::vec2(0, 0);
    case TOP:
      return glm::vec2(1, 1);
    case WEST:
    case EAST:
      return glm::vec2(1, 0);
    case NORTH:
    case SOUTH:
      return glm::vec2(0, 1);
    }
  }
};
