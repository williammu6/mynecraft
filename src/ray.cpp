#include "ray.hpp"
#include "gfx/primitive.hpp"
#include "level/blocks/block.hpp"

std::optional<Intersection> Ray::intersection(const struct World &world,
                                              float reach) {
  glm::vec3 rayPosition = _origin;
  glm::vec3 distanceTraveled = glm::vec3(0);
  glm::vec3 maxReachPosition = _origin + _direction * reach;
  Direction direction;

  float halfBlock = 0.5f;
  int steps = reach;

  while (glm::distance(_origin, rayPosition) <= reach) {
    std::optional<Block *> block =
        state.world->globalPositionToBlock(rayPosition + halfBlock);
    if (block.has_value()) {
      return (Intersection){.position = rayPosition + halfBlock,
                            .faceDirection = DIRECTIONS[direction]};
    }
    rayPosition += _direction / 5.0f;
  }
  printf("Out of reach\n");

  return std::nullopt;
}
