#pragma once

#include "../gfx/gfx.hpp"
#include "../common.hpp"

enum Face
{
    TOP = 0,
    BOTTOM,
    LEFT_RIGHT,
    FRONT_BACK
};

struct Element {
    std::string name;

    glm::vec2 texture_offset(enum Face face);

    Element() { }
};
