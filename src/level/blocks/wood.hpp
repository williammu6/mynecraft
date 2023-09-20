#pragma once

#include "block_type.hpp"

enum class TreeType { NORMAL = 0, JUNGLE };

struct Wood : BlockType {
  TreeType wood_variant;
  Wood(TreeType _wood_variant) {
    name = "wood";
    solid = true;
    wood_variant = _wood_variant;
  }
  glm::vec2 texture_offset(Direction direction) {
    switch (direction) {
    case TOP:
    case DOWN:
      if (wood_variant == TreeType::NORMAL)
        return glm::vec2(4, 0);
      return glm::vec2(2, 7);
    case WEST:
    case EAST:
      if (wood_variant == TreeType::NORMAL)
        return glm::vec2(3, 2);
      return glm::vec2(1, 7);
    default:
      if (wood_variant == TreeType::NORMAL)
        return glm::vec2(3, 1);
      return glm::vec2(0, 7);
    }
  }
};
