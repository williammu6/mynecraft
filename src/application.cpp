#include "application.hpp"
#include <cmath>
#include <iostream>

Params getParams(char **argv) {
  return {.seed = std::atoi(argv[1])};
}

struct State global_state;
State &state = global_state;

Application::Application(char **argv) {
  params = getParams(argv);
}

void Application::run() {
  Renderer renderer;
  state.renderer = &renderer;
  state.running = true;
  state.world = new World(this->params.seed);

  setupMouseInput();

  this->loop();

  state.window->terminate();
}

void Application::loop() {
  GLFWwindow *window = state.window->p_getWindow();

  int frames = 0;
  double deltaTime, lastFrame, currentTime;
  double previousTime = glfwGetTime();

  while (state.running) {
    currentTime = glfwGetTime();
    frames++;
    deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;
    this->inputHandler(window, deltaTime);
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
  state.world->tick();
  // state.world->sky->render();
  // state.sun_position = state.camera.position;
  state.camera.update();
  state.window->update();
}

void Application::inputHandler(GLFWwindow *window, double delta_time) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    state.running = false;

  float cameraSpeed = 48 * delta_time;
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    state.wireframe_mode = !state.wireframe_mode;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    state.camera.position += cameraSpeed * state.camera.front;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    state.camera.position -= cameraSpeed * state.camera.front;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    state.camera.position -=
        glm::normalize(glm::cross(state.camera.front, state.camera.up)) *
        cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    state.camera.position +=
        glm::normalize(glm::cross(state.camera.front, state.camera.up)) *
        cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    state.camera.position -= glm::vec3(0, 1, 0) * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    state.camera.position += glm::vec3(0, 1, 0) * cameraSpeed;
}

Application::~Application() {
  state.window->terminate();
}
