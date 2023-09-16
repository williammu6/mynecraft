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

void Window::loop(std::function<void()> update_world_fn,
                  std::function<void(GLFWwindow *, double)> input_handler_fn) {
  int frames = 0;
  double delta_time, last_frame;
  double previous_time = glfwGetTime();
  while (state.running) {
    float current_time = glfwGetTime();
    delta_time = current_time - last_frame;
    frames++;
    input_handler_fn(this->p_getWindow(), delta_time);
    last_frame = current_time;
    if (current_time - previous_time >= 1.0) {
      DEBUG(frames);
      previous_time = current_time;
      frames = 0;
    }

    update_world_fn();
  }
}
