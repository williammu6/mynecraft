#ifndef RAY_H
#define RAY_H

#include "../gfx/direction.hpp"
#include "../scene/blocks/block.hpp"
#include "../scene/world.hpp"
#include "../state.hpp"
#include "glm/glm.hpp"
#include <optional>

namespace ray {
struct Intersection {
  glm::vec3 position;
  glm::vec3 faceSide;
};

std::optional<Intersection> cast(glm::vec3 origin, glm::vec3 direction,
                                 std::function<bool(const glm::vec3&)> collision,
                                 float reach);

}; // namespace ray
#endif
