#include "window.hpp"
#include "../state.hpp"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>

Window::Window() {
  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  window = glfwCreateWindow(state.windowWidth, state.windowHeight, "Mynecraft",
                            NULL, NULL);

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Error initializing OpenGL" << std::endl;
    exit(0);
  }

  glfwSwapInterval(1);
}

void Window::update() {
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void Window::clear() {
  glClearColor(0.2f, 0.5f, 1.0f, 1.0f);
}

void Window::prepareRender2d() {
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_CLAMP);
  glDisable(GL_BLEND);
}

void Window::prepareRender3d() {
  glEnable(GL_BLEND);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glPolygonMode(GL_FRONT_AND_BACK, state.wireframeMode ? GL_LINE : GL_FILL);

  glPolygonOffset(1.0, 1.0);
  glEnable(GL_POLYGON_OFFSET_FILL);
}

Window::~Window() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

GLFWwindow *Window::p_getWindow() {
  return window;
}
