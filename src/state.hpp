#pragma once

#include "gfx/renderer.hpp"
#include "gfx/window.hpp"
#include "gfx/camera.hpp"
#include "element/element.hpp"
#include "element/grass.hpp"

#include <map>

struct State
{
    int windowWidth, windowHeight;
    Window *window;
    Renderer::Renderer2D renderer2d;
    Camera camera;
    std::map<const char*, Element> elements {
        { "grass", Grass() }
    };
    bool running;
};

extern State &state;
