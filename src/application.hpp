#pragma once

#include "gfx/window.hpp"
#include "gfx/shader.hpp"
#include "gfx/renderer.hpp"
#include "gfx/camera.hpp"
#include "gfx/texture.hpp"
#include "common.hpp"
#include "state.hpp"

class Application
{
public:
    Application();
    ~Application();
    void run();
    void inputHandler(GLFWwindow *window);
};
