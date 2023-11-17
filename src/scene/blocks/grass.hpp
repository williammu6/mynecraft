#pragma once

#include "block.hpp"

struct Grass : Block {
  Grass() {
    name = "grass";
    solid = true;
  }
  glm::vec2 textureOffset(Direction direction) {
    rotation = TextureRotation::DEGREES_0;
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
      rotation = TextureRotation::DEGREES_270;
      return glm::vec2(1, 0);
    }
  }
};
