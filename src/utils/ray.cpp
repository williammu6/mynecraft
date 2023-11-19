#include "ray.hpp"
#include "../scene/blocks/block.hpp"

/**
 TODOS
 not inject the world, instead, inject a method that does the collision detection
 ray should't know about the world
 although this works, it could probably be optimized
*/

std::optional<Intersection> Ray::intersection(const struct World &world,
                                              float reach) {
  glm::vec3 rayPosition = _origin;
  glm::vec3 faceSide(0);

  bool success = false;
  float halfBlock = 0.5f;
  glm::vec3 stepSize = _direction / 5.0f;

  while (glm::distance(_origin, rayPosition) <= reach) {
    std::optional<Block *> maybeBlock =
        state.world->globalPositionToBlock(rayPosition + halfBlock);

    rayPosition.z += stepSize.z;
    if (maybeBlock.has_value()) {
      faceSide = _direction.z < 0 ? DIRECTIONS[SOUTH] : DIRECTIONS[NORTH];
      success = true;
      break;
    } else {
      rayPosition.z -= stepSize.z;
    }

    rayPosition.x += stepSize.x;
    maybeBlock = state.world->globalPositionToBlock(rayPosition + halfBlock);
    if (maybeBlock.has_value()) {
      faceSide = _direction.x < 0 ? DIRECTIONS[EAST] : DIRECTIONS[WEST];
      success = true;
      break;
    } else {
      rayPosition.x -= stepSize.x;
    }

    rayPosition.y += stepSize.y;
    maybeBlock = state.world->globalPositionToBlock(rayPosition + halfBlock);
    if (maybeBlock.has_value()) {
      faceSide = _direction.y < 0 ? DIRECTIONS[TOP] : DIRECTIONS[DOWN];
      success = true;
      break;
    } else {
      rayPosition.y -= stepSize.y;
    }

    rayPosition += stepSize;
  }

  if (success) {
    return (Intersection){
        .position = rayPosition,
        .blockPosition =
            state.world->globalPositionToBlockPosition(rayPosition + halfBlock),
        .placeBlockChunk = state.world->globalPositionToChunk(
            rayPosition + (glm::vec3)faceSide + halfBlock),
        .placeBlockPosition = state.world->globalPositionToBlockPosition(
            rayPosition + (glm::vec3)faceSide + halfBlock)};
  }

  return std::nullopt;
}
