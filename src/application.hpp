#pragma once

#include "gfx/window.hpp"
#include "gfx/shader.hpp"

class Application {
    private:
        Window* m_Window;
        unsigned int m_VertexBuffer, m_VertexArray, m_IndexBuffer;
    public:
        Application();
        ~Application();
        Window* getWindow();
        void run();
};
