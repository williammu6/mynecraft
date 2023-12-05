#ifndef APPLICATION_H
#define APPLICATION_H

#include "gfx/blockOutline.hpp"
#include "gfx/crosshair.hpp"
#include "player.hpp"
#include "scene/world.hpp"

struct Params {
  int seed;
};

Params getParams(char **argv);

class Application {
public:
  World *world;
  std::unique_ptr<BlockOutline> blockOutline;
  Application(char **argv);
  ~Application(){};
  void run();
  void update();
  void loop();
  void tick();
  void inputHandler(GLFWwindow *window, double delta_time);

private:
  struct Params params;
  Crosshair *crosshair;
  std::shared_ptr<Player> player;
};

#endif
