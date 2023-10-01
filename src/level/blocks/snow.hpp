#pragma once

#include "block.hpp"

struct Snow : Block {
  Snow() {
    name = "snow";
    solid = true;
  }
  glm::vec2 texture_offset(Direction direction) {
    rotation = TextureRotation::DEGREES_0;
    switch (direction) {
    case WEST:
    case EAST:
      return glm::vec2(6, 1);
    case NORTH:
    case SOUTH:
      rotation = TextureRotation::DEGREES_270;
      return glm::vec2(6, 1);
    case TOP:
      return glm::vec2(5, 1);
    case DOWN:
      return glm::vec2(0, 0);
    }
  }
};
