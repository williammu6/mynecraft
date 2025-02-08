#include "application.hpp"
#include "gfx/block_outline.hpp"
#include "glad/glad.h"
#include "state.hpp"
#include "utils/debug.hpp"

Params getParams(char **argv) {
  return {.seed = std::atoi(argv[1])};
}

struct State global_state;
State &state = global_state;

Application::Application(char **argv) {
  params = getParams(argv);
  player = std::make_shared<Player>(state.window->p_getWindow(), &state.camera);
  crosshair = new Crosshair(state.windowWidth, state.windowHeight);
  crosshair->prepare();
  blockOutline = std::make_unique<BlockOutline>();
  blockOutline->setup();
}

void Application::run() {
  Renderer renderer;
  state.renderer = &renderer;
  state.running = true;
  state.world = new World(this->params.seed);

  this->loop();
}

void Application::loop() {
  int fps = 0;
  double deltaTime, lastFrame, currentTime;
  double previousTime = glfwGetTime();

  // removed frame rate limit
  glfwSwapInterval(0);

  while (state.running) {
    currentTime = glfwGetTime();
    fps++;
    deltaTime = currentTime - lastFrame;
    state.deltaTime = deltaTime;
    lastFrame = currentTime;
    player->keyboardCallback(deltaTime);
    tick();

    if (currentTime - previousTime >= 1.0) {
      // DEBUG(fps);
      previousTime = currentTime;
      fps = 0;
    }
  }
}

void Application::tick() {
  state.window->clear();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // 3d pass
  state.window->prepareRender3d();

  state.world->tick();
  state.camera.update();
  player->tick();

  if (player->lookIntersection.has_value()) {
    blockOutline->draw(player->lookIntersection.value().position);
  }

  // 2d pass
  state.window->prepareRender2d();
  crosshair->render();

  state.window->update();
}
