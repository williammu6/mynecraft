#include "window.hpp"
#include "../state.hpp"
#include "GLFW/glfw3.h"
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, state.wireframe_mode ? GL_LINE : GL_FILL);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_CLAMP);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

Window *Window::create() { return new Window(); }

void Window::terminate() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

GLFWwindow *Window::p_getWindow() { return window; }
