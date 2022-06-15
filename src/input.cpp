#include "input.hpp"

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  state.camera.look_at(xpos, ypos);
}

void setup_mouse_input() {
  glfwSetInputMode(state.window->p_getWindow(), GLFW_CURSOR,
                   GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(state.window->p_getWindow(), mouse_callback);
}
