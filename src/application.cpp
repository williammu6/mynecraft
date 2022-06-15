#include "application.hpp"

struct State global_state;
State &state = global_state;

Application::Application() {
  state.windowWidth = 1280;
  state.windowHeight = 720;

  state.window = Window::create();
}

void Application::run() {
  state.running = true;
  state.camera = Camera(state.windowWidth, state.windowHeight);

  setup_mouse_input();

  this->world = new World(16);

  double previous_time = glfwGetTime();

  while (state.running) {
    float current_time = glfwGetTime();
    this->delta_time = current_time - this->last_frame;

    update();

    input_handler(state.window->p_getWindow());
    this->last_frame = current_time;
    if (current_time - previous_time >= 1.0) {
      previous_time = current_time;
    }
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

  float cameraSpeed = 10 * this->delta_time;
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    state.wireframe_mode = !state.wireframe_mode;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    state.camera.cameraPos += cameraSpeed * state.camera.cameraFront;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    state.camera.cameraPos -= cameraSpeed * state.camera.cameraFront;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    state.camera.cameraPos -=
        glm::normalize(
            glm::cross(state.camera.cameraFront, state.camera.cameraUp)) *
        cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    state.camera.cameraPos +=
        glm::normalize(
            glm::cross(state.camera.cameraFront, state.camera.cameraUp)) *
        cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    state.camera.cameraPos -= glm::vec3(0, 1, 0) * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    state.camera.cameraPos += glm::vec3(0, 1, 0) * cameraSpeed;
}

Application::~Application() { state.window->terminate(); }
