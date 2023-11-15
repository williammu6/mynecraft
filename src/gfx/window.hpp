#ifndef WINDOW_H
#define WINDOW_H

#include "gfx.hpp"

struct WindowProps {
  int width, height;
};

class Window {
private:
  GLFWwindow *window;

public:
  Window();
  ~Window();
  void processInput();
  void update();
  void clear();
  int shouldClose();
  GLFWwindow *p_getWindow();
  void prepareRender2d();
  void prepareRender3d();
};

#endif
