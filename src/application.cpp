#include "application.hpp"
#include <cmath>
#include <iostream>

#define TAU (M_PI * 2.0)

using namespace std::chrono;

struct State global_state;
State &state = global_state;

Application::Application() {
  state.windowWidth = 1700;
  state.windowHeight = 1200;

  state.window = Window::create();
}

void Application::run() {
  state.running = true;
  state.camera = Camera(state.windowWidth, state.windowHeight);

  setup_mouse_input();

  Renderer renderer = Renderer();
  state.renderer = &renderer;

  this->world = new World(16, 123456);

  double previous_time = glfwGetTime();

  int frames = 0;
  double timer;
  double speed = 1;

  state.sun_position = glm::vec3(140, 150, 120);

  while (state.running) {
    float current_time = glfwGetTime();
    this->delta_time = current_time - this->last_frame;

    frames++;

    input_handler(state.window->p_getWindow());
    this->last_frame = current_time;
    if (current_time - previous_time >= 1.0) {
      std::cout << "FPS: " << frames << std::endl;
      previous_time = current_time;
      frames = 0;
    }

    update();
    glm::vec3 center = state.camera.position;
    timer += delta_time * speed;
    if (timer > TAU) timer -= TAU;
    state.sun_position.z = cos(M_PI_2 * timer)*400 + center.z;
    state.sun_position.y = sin(M_PI_2 * timer)*400 + center.y;
    state.sun_position.x = state.camera.position.x;
  }

  state.window->terminate();
}

void Application::update() {
  state.window->clear();
  world->render();
  // world->sky->render();
  state.camera.update();
  state.window->update();
}

void Application::input_handler(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    state.running = false;

  float cameraSpeed = 15 * this->delta_time;
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
