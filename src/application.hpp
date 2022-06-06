#pragma once

#include "gfx/window.hpp"
#include "gfx/shader.hpp"
#include "gfx/renderer.hpp"

class Application {
    private:
        Window* m_Window;
        Renderer* m_Renderer;
        struct WindowProps windowProps;
    public:
        Application();
        ~Application();
        Window* getWindow();
        Renderer* getRenderer();
        void run();
        void inputHandler(GLFWwindow* window);
};
