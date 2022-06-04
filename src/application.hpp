#pragma once

#include "gfx/window.hpp"

class Application {
    private:
        Window* m_Window;
    public:
        Application();
        ~Application();
        Window* getWindow();
        void run();
};
