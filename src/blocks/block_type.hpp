#pragma once

#include "../common.hpp"
#include "../gfx/gfx.hpp"

enum Face { TOP = 0, FRONT, LEFT, RIGHT, BACK, BOTTOM };

struct BlockType {
  const char *name;
  bool solid;

  virtual ~BlockType(){};
  virtual glm::vec2 texture_offset(Face face) = 0;
};
