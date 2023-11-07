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
  glClearColor(0.0f, 0.6f, 1.0f, 1.0f);
}

void Window::prepareRender2d() {
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_CLAMP);
  glDisable(GL_BLEND);
}

void Window::prepareRender3d() {
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_CLAMP);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, state.wireframe_mode ? GL_LINE : GL_FILL);
  glDepthFunc(GL_LESS);
  glCullFace(GL_BACK);
}

void Window::terminate() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

GLFWwindow *Window::p_getWindow() {
  return window;
}
