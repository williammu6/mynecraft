#pragma once

#include "common.hpp"
#include "gfx/camera.hpp"
#include "gfx/shader.hpp"
#include "gfx/texture.hpp"
#include "gfx/window.hpp"
#include "gfx/world/world.hpp"
#include "input.hpp"
#include "state.hpp"

class Application {
public:
  World *world;
  double delta_time, last_frame;
  Application();
  ~Application();
  void run();
  void update();
  void input_handler(GLFWwindow *window);
};
