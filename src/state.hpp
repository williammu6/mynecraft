#pragma once

#include "gfx/camera.hpp"
#include "gfx/renderer.hpp"
#include "gfx/window.hpp"
#include "level/blocks/block.hpp"

struct State {
  int windowWidth;
  int windowHeight;
  std::shared_ptr<Window> window;
  Camera camera;
  struct World *world;
  bool wireframe_mode = false;
  bool running = false;
  Renderer *renderer;
  glm::vec3 sun_position = {0, 50, 0};
  float tick;
  int frames = 0;

  State() {
    windowWidth = 1400;
    windowHeight = 1000;
    window = std::make_unique<Window>();
    camera = Camera(windowWidth, windowHeight);
  }
};

extern State &state;
