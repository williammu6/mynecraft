#include "ray.hpp"

std::optional<ray::Intersection>
ray::cast(glm::vec3 origin, glm::vec3 direction,
          std::function<bool(const glm::vec3 &)> collision, float reach) {
  if (direction == glm::vec3(0))
    return std::nullopt;

  glm::vec3 rayPosition = origin;
  float halfBlock = 0.5f;
  glm::vec3 stepSize = direction / 5.0f;

  while (glm::distance(origin, rayPosition) <= reach) {
    rayPosition.z += stepSize.z;
    if (collision(rayPosition + halfBlock)) {
      return (ray::Intersection){
          .position = rayPosition + halfBlock,
          .faceSide = direction.z < 0 ? DIRECTIONS[SOUTH] : DIRECTIONS[NORTH],
      };
    } else {
      rayPosition.z -= stepSize.z;
    }

    rayPosition.x += stepSize.x;
    if (collision(rayPosition + halfBlock)) {
      return (ray::Intersection){
          .position = rayPosition + halfBlock,
          .faceSide = direction.x < 0 ? DIRECTIONS[EAST] : DIRECTIONS[WEST],
      };
    } else {
      rayPosition.x -= stepSize.x;
    }

    rayPosition.y += stepSize.y;
    if (collision(rayPosition + halfBlock)) {
      return (ray::Intersection){
          .position = rayPosition + halfBlock,
          .faceSide = direction.y < 0 ? DIRECTIONS[TOP] : DIRECTIONS[DOWN],
      };
    } else {
      rayPosition.y -= stepSize.y;
    }

    rayPosition += stepSize;
  }

  return std::nullopt;
}
