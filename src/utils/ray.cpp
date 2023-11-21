#include "ray.hpp"
#include "../scene/blocks/block.hpp"

std::optional<ray::Intersection> ray::cast(glm::vec3 origin,
                                           glm::vec3 direction,
                                           bool (*collisionCheck)(glm::vec3),
                                           float reach) {
  glm::vec3 rayPosition = origin;
  glm::vec3 faceSide(0);

  bool success = false;
  float halfBlock = 0.5f;
  glm::vec3 stepSize = direction / 5.0f;

  while (glm::distance(origin, rayPosition) <= reach) {
    rayPosition.z += stepSize.z;
    if (collisionCheck(rayPosition + halfBlock)) {
      return (ray::Intersection){
          .position = rayPosition + halfBlock,
          .faceSide = direction.z < 0 ? DIRECTIONS[SOUTH] : DIRECTIONS[NORTH],
      };
    } else {
      rayPosition.z -= stepSize.z;
    }

    rayPosition.x += stepSize.x;
    if (collisionCheck(rayPosition + halfBlock)) {
      return (ray::Intersection){
          .position = rayPosition + halfBlock,
          .faceSide = direction.x < 0 ? DIRECTIONS[EAST] : DIRECTIONS[WEST],
      };
    } else {
      rayPosition.x -= stepSize.x;
    }

    rayPosition.y += stepSize.y;
    if (collisionCheck(rayPosition + halfBlock)) {
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
