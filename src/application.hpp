#pragma once

#include "gfx/window.hpp"
#include "gfx/shader.hpp"

class Application {
    private:
        Window* m_Window;
        bool shouldStop;
        unsigned int m_VertexBuffer, m_VertexArray, m_IndexBuffer, texture;
    public:
        Application();
        ~Application();
        Window* getWindow();
        void run();
        void stop();
};
