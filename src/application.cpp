#include "application.hpp"
#include <cmath>
#include <iostream>

#define TAU (M_PI * 2.0)

Params get_params(char **argv) { return {.seed = std::atoi(argv[1])}; }

struct State global_state;
State &state = global_state;

Application::Application() {}

void Application::run(char **argv) {
  Params params = get_params(argv);
  state.running = true;

  Renderer renderer;
  state.renderer = &renderer;

  setup_mouse_input();

  this->world = new World(16, params.seed);

  state.window->loop([this]() { update(); },
                     [this](GLFWwindow *window, double delta_time) {
                       input_handler(window, delta_time);
                     });

  state.window->terminate();
}

void Application::update() {
  state.window->clear();
  world->render();
  world->sky->render();
  state.camera.update();
  state.window->update();
}

void Application::input_handler(GLFWwindow *window, double delta_time) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    state.running = false;

  float cameraSpeed = 15 * delta_time;
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

Application::~Application() { state.window->terminate(); }
