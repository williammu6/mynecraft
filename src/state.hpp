#pragma once

#include "gfx/camera.hpp"
#include "gfx/renderer.hpp"
#include "gfx/window.hpp"
#include "level/blocks/block_type.hpp"

struct State {
  int windowWidth = 1200;
  int windowHeight = 800;
  Window *window;
  Camera camera;
  bool wireframe_mode = false;
  bool running = false;
  Renderer *renderer;
  glm::vec3 sun_position = {0, 10, 0};
  float tick;
  int frames = 0;

  State() {
    windowWidth = 1700;
    windowHeight = 1200;
    window = Window::create();
    camera = Camera(windowWidth, windowHeight);
  }
};

extern State &state;
