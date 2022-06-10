#pragma once

#include "gfx/window.hpp"
#include "gfx/camera.hpp"
#include "element/element.hpp"
#include "element/grass.hpp"

#include <map>

struct State
{
    int windowWidth, windowHeight;
    Window *window;
    Camera camera;
    bool wireframe_mode = false;
    std::map<const char*, Grass> elements {
        { "grass", Grass() }
    };
    bool running;
};

extern State &state;
