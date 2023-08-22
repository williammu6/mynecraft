#pragma once

#include "../../gfx/gfx.hpp"
#include "../direction.hpp"

struct BlockType {
  const char *name;
  bool solid;

  virtual ~BlockType(){};
  virtual glm::vec2 texture_offset(enum Direction direction) = 0;
};
