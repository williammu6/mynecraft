#pragma once

#include "block.hpp"

enum class TreeType { NORMAL = 0, JUNGLE };

struct Wood : Block {
  TreeType wood_variant;
  Wood(TreeType _wood_variant) {
    name = "wood";
    solid = true;
    wood_variant = _wood_variant;
  }
  glm::vec2 texture_offset(Direction direction) {
    rotation = TextureRotation::DEGREES_0;
    switch (direction) {
    case TOP:
    case DOWN:
      if (wood_variant == TreeType::NORMAL) {
        return glm::vec2(4, 0);
      }
      return glm::vec2(1, 7);
    case WEST:
    case EAST:
      if (wood_variant == TreeType::NORMAL) {
        rotation = TextureRotation::DEGREES_270;
        return glm::vec2(3, 1);
      }
      return glm::vec2(1, 7);
    default:
      if (wood_variant == TreeType::NORMAL) {
        return glm::vec2(3, 1);
      }
      return glm::vec2(1, 7);
    }
  }
};
