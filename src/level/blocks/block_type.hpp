#pragma once

#include "../../gfx/direction.hpp"
#include "../../gfx/gfx.hpp"

struct BlockType {
  const char *name;
  bool solid;
  bool transparent = false;

  virtual ~BlockType(){};
  virtual glm::vec2 texture_offset(Direction direction) = 0;
};
