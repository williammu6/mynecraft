#include "element.hpp"

struct Grass : public Element {
    glm::vec2 texture_offset(enum Face face) {
        switch (face) {
            case TOP:
                return glm::vec2(0, 1);
            case BOTTOM: 
                return glm::vec2(0, 2);
            case LEFT_RIGHT:
                return glm::vec2(0, 0);
            case FRONT_BACK:
                return glm::vec2(0, 0);
        }
    }

    Grass() {
        this->name = "grass";
    }
};
