#ifndef STATE_H
#define STATE_H

#include "gfx/camera.hpp"
#include "gfx/crosshair.hpp"
#include "gfx/renderer.hpp"
#include "gfx/window.hpp"
#include "scene/world.hpp"
#include <memory>
#include <unordered_map>

struct State {
  Camera camera;
  Renderer *renderer;

  bool running = false;
  bool wireframeMode = false;
  float aspectRatio;
  float deltaTime = 0;
  float tick;
  int frames = 0;
  int windowHeight;
  int windowWidth;

  std::shared_ptr<Window> window;
  std::unordered_map<int, bool> pressed;
  Crosshair *crosshair;
  struct World *world;

  State() {
    windowWidth = 1800;
    windowHeight = 1300;

    aspectRatio =
        static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

    window = std::make_unique<Window>();
    camera = Camera(windowWidth, windowHeight);
  }
};

extern State &state;

#endif
