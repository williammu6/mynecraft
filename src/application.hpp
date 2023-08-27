#ifndef APPLICATION_H
#define APPLICATION_H

#include "common.hpp"
#include "gfx/camera.hpp"
#include "gfx/renderer.hpp"
#include "gfx/shader.hpp"
#include "gfx/texture.hpp"
#include "gfx/window.hpp"
#include "level/world.hpp"
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

#endif
