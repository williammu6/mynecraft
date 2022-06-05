#pragma once

#include "gfx.hpp"
#include "functional"
#include <stdlib.h>

struct WindowProps {
    int width, height;
};

class Window {
    private:
        void* inputHandler;
        GLFWwindow* window;
    public:
        Window(int width, int height);
        static Window* create(const WindowProps& props);
        void terminate();
        void processInput(GLFWwindow* window);
        void update();
        void clear();
};
