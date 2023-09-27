#pragma once

#include "../../gfx/direction.hpp"
#include "../../gfx/gfx.hpp"

struct Block {
  const char *name;
  bool solid;
  bool transparent = false;

  ~Block(){};
  virtual glm::vec2 texture_offset(Direction direction) = 0;
};
