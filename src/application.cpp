#include "application.hpp"
#include "GLFW/glfw3.h"
#include "gfx/blockOutline.hpp"
#include "glad/glad.h"
#include "glm/ext/quaternion_common.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/fwd.hpp"
#include "scene/blocks/cobblestone.hpp"
#include <cmath>
#include <iostream>

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
  int frames = 0;
  double deltaTime, lastFrame, currentTime;
  double previousTime = glfwGetTime();

  while (state.running) {
    currentTime = glfwGetTime();
    frames++;
    deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;
    player->keyboardCallback(deltaTime);

    if (currentTime - previousTime >= 1.0) {
      DEBUG(frames);
      previousTime = currentTime;
      frames = 0;
    }

    this->tick();
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
