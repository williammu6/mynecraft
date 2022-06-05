#pragma once

#include "gfx/window.hpp"
#include "gfx/shader.hpp"

class Application {
    private:
        Window* m_Window;
        bool shouldStop;
        struct WindowProps windowProps;
    public:
        Application();
        ~Application();
        Window* getWindow();
        void run();
        void stop();
};
