#pragma once

#include "../../gfx/direction.hpp"
#include "../../gfx/gfx.hpp"

struct Block {
  const char *name;
  bool solid = true;
  bool transparent = false;
  bool liquid = false;

  ~Block(){};
  virtual glm::vec2 texture_offset(Direction direction) = 0;
  bool drawable() {
    return solid || liquid;
  }
};
