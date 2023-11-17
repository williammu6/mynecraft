#pragma once

#include "block.hpp"

struct Cactus : Block {
  Cactus() {
    name = "cactus";
    solid = true;
  }
  glm::vec2 textureOffset(Direction direction) {
    rotation = TextureRotation::DEGREES_0;
    switch (direction) {
    case NORTH:
    case SOUTH:
      rotation = TextureRotation::DEGREES_270;
      return glm::vec2(7, 0);
    case WEST:
    case EAST:
      return glm::vec2(7, 0);
    default:
      return glm::vec2(6, 0);
    }
  }
};
