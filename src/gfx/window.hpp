#pragma once

#include "gfx.hpp"
#include <stdlib.h>

class Window {
    private:
        GLFWwindow* window;
    public:
        Window(int width, int height);
        static Window* create(int width, int height);
        void terminate();
        void loop();
};
