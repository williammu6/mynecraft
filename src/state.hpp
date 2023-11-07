#pragma once

#include "gfx/camera.hpp"
#include "gfx/renderer.hpp"
#include "gfx/window.hpp"
#include "level/blocks/block.hpp"

struct State {
  Camera camera;
  Renderer *renderer;
  bool running = false;
  bool wireframe_mode = false;
  float aspectRatio;
  float tick;
  glm::vec3 sun_position = {0, 50, 0};
  int frames = 0;
  int windowHeight;
  int windowWidth;
  std::shared_ptr<Window> window;
  struct World *world;

  State() {
    windowWidth = 1400;
    windowHeight = 1000;

    aspectRatio =
        static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

    window = std::make_unique<Window>();
    camera = Camera(windowWidth, windowHeight);
  }
};

extern State &state;
