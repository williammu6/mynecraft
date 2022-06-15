#pragma once

#include "block_type/block_type.hpp"
#include "block_type/grass.hpp"
#include "gfx/camera.hpp"
#include "gfx/window.hpp"

#include <map>

struct State {
  int windowWidth, windowHeight;
  Window *window;
  Camera camera;
  bool wireframe_mode = false;
  std::map<const char *, Grass> elements{{"grass", Grass()}};
  bool running;
};

extern State &state;
