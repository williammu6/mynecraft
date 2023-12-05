#ifndef RAY_H
#define RAY_H

#include "../gfx/cube_face.hpp"
#include <glm/glm.hpp>
#include <optional>
#include <functional>

namespace ray {
struct Intersection {
  glm::vec3 position;
  glm::vec3 faceSide;
  Direction direction;
};

std::optional<Intersection>
cast(glm::vec3 origin, glm::vec3 direction,
     std::function<bool(const glm::vec3 &)> collision, float reach);

}; // namespace ray
#endif
