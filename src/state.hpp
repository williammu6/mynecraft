#pragma once

#include "level/blocks/block_type.hpp"
#include "gfx/camera.hpp"
#include "gfx/renderer.hpp"
#include "gfx/window.hpp"
// #include "level/sky.hpp"

struct State {
  int windowWidth, windowHeight;
  Window *window;
  Camera camera;
  bool wireframe_mode = false;
  bool running;
  Renderer *renderer;
  glm::vec3 sun_position;
  // Sky *sky;
};

extern State &state;
