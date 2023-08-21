#pragma once

#include "../common.hpp"
#include "../gfx/gfx.hpp"

enum Face { TOP = 0, BOTTOM = 1, LEFT_RIGHT = 2, FRONT_BACK = 3 };

struct BlockType {
  const char *name;
  bool solid;

  virtual ~BlockType(){};
  virtual glm::vec2 texture_offset(Face face) = 0;
};
