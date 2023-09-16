#pragma once

#include "functional"
#include "gfx.hpp"
#include <stdlib.h>

struct WindowProps {
  int width, height;
};

class Window {
private:
  GLFWwindow *window;

public:
  Window();
  static Window *create();
  void terminate();
  void processInput();
  void update();
  void clear();
  int shouldClose();
  GLFWwindow *p_getWindow();
  void loop(std::function<void()> update_world_fn,
            std::function<void(GLFWwindow *, double)> input_handler_fn);
};
