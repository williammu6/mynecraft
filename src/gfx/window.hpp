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
  void terminate();
  void processInput();
  void update();
  void clear();
  int shouldClose();
  GLFWwindow *p_getWindow();
  void prepareRender2d();
  void prepareRender3d();
};
