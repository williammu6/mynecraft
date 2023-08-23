#include "application.hpp"
#include <iostream>
#include <memory>

struct State global_state;
State &state = global_state;

Application::Application() {
  state.windowWidth = 2000;
  state.windowHeight = 1000;

  state.window = Window::create();
}

void Application::run() {
  state.running = true;
  state.camera = Camera(state.windowWidth, state.windowHeight);

  setup_mouse_input();

  Renderer renderer = {
      .texture_atlas = new TextureAtlas("res/textures.png"),
      .shader = new Shader(
          "res/shaders/basicTexture.vert", "res/shaders/basicTexture.frag")
  };

  state.renderer = &renderer;

  this->world = new World(16, 123456);

  double previous_time = glfwGetTime();

  int frames = 0;

  state.sun_position = glm::vec3(0, 400, 0);

  while (state.running) {
    float current_time = glfwGetTime();
    this->delta_time = current_time - this->last_frame;

    frames++;

    input_handler(state.window->p_getWindow());
    this->last_frame = current_time;
    if (current_time - previous_time >= 1.0) {
      previous_time = current_time;
      // std::cout << frames << std::endl;
      frames = 0;
    }

    update();
  }
  state.window->terminate();
}
void Application::update() {
  state.window->clear();
  world->render();
  state.camera.update();
  state.window->update();
}

void Application::input_handler(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    state.running = false;

  float cameraSpeed = 35 * this->delta_time;
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
