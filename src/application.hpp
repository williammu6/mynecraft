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
#include "gfx/crosshair.hpp"

struct Params {
  int seed;
};

Params getParams(char **argv);

class Application {
public:
  World *world;
  Application(char **argv);
  ~Application();
  void run();
  void update();
  void loop();
  void tick();
  void inputHandler(GLFWwindow *window, double delta_time);

private:
  struct Params params;
};

#endif
