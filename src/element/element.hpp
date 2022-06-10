#pragma once

#include "../gfx/gfx.hpp"
#include "../common.hpp"

enum Face
{
    TOP = 0,
    BOTTOM = 1,
    LEFT_RIGHT = 2,
    FRONT_BACK = 3
};

struct Element {
    std::string name;

    glm::vec2 texture_offset(Face face);

    Element() { }
};
