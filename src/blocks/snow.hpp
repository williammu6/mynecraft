#pragma once

#include "block_type.hpp"

struct Snow : BlockType {
  Snow() {
    name = "snow";
    solid = true;
  }
  glm::vec2 texture_offset(Face face) {
    switch (face) {
    case LEFT_RIGHT:
    case FRONT_BACK:
      return glm::vec2(6, 1);
    case TOP:
      return glm::vec2(5, 1);
    case BOTTOM:
      return glm::vec2(0, 0);
    }
  }
};
