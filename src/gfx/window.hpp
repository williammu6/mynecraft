#pragma once

#include "gfx.hpp"
#include "functional"
#include <stdlib.h>

struct WindowProps
{
    int width, height;
};

class Window
{
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
};
