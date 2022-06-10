#pragma once

#include "gfx/window.hpp"
#include "gfx/shader.hpp"
#include "gfx/camera.hpp"
#include "gfx/texture.hpp"
#include "common.hpp"
#include "state.hpp"

class Application
{
    public: 
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    Application();
    ~Application();
    void run();
    void inputHandler(GLFWwindow *window);
};
