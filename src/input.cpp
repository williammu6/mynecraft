#include "input.hpp"

void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
  state.camera.lookAt(xpos, ypos);
}

void setupMouseInput() {
  glfwSetInputMode(state.window->p_getWindow(), GLFW_CURSOR,
                   GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(state.window->p_getWindow(), mouseCallback);
}
