#pragma once

#include "element.hpp"

struct Grass : public Element {
    glm::vec2 texture_offset(Face face) {
        switch (face) {
            case BOTTOM: 
                return glm::vec2(0, 0);
            case TOP:
                return glm::vec2(1, 1);
            case LEFT_RIGHT:
                return glm::vec2(1, 0);
            case FRONT_BACK:
                return glm::vec2(0, 1);
        }
    }

    Grass() {
        this->name = "grass";
    }
};
