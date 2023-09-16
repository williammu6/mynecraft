#ifndef APPLICATION_H
#define APPLICATION_H

#include "common.hpp"
#include "gfx/camera.hpp"
#include "gfx/renderer.hpp"
#include "gfx/shader.hpp"
#include "gfx/texture.hpp"
#include "gfx/window.hpp"
#include "input.hpp"
#include "level/world.hpp"
#include "state.hpp"

struct Params {
  char* seed;
};

Params get_params(char **argv);

class Application {
public:
  World *world;
  Application();
  ~Application();
  void run(char **argv);
  void update();
  void input_handler(GLFWwindow *window, double delta_time);
};

#endif
