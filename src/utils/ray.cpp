#include "ray.hpp"

std::optional<ray::Intersection>
ray::cast(glm::vec3 origin, glm::vec3 direction,
          std::function<bool(const glm::vec3 &)> collision, float reach) {
  if (direction == glm::vec3(0))
    return std::nullopt;

  glm::vec3 rayDirection = glm::normalize(direction);
  glm::ivec3 voxel = glm::floor(origin + glm::vec3(0.5f));
  glm::ivec3 step(rayDirection.x > 0 ? 1 : -1, rayDirection.y > 0 ? 1 : -1,
                  rayDirection.z > 0 ? 1 : -1);
  glm::vec3 halfBlock(0.5f);

  glm::vec3 tDelta{
      rayDirection.x != 0.0f ? glm::abs(1.0f / rayDirection.x)
                             : std::numeric_limits<float>::max(),
      rayDirection.y != 0.0f ? glm::abs(1.0f / rayDirection.y)
                             : std::numeric_limits<float>::max(),
      rayDirection.z != 0.0f ? glm::abs(1.0f / rayDirection.z)
                             : std::numeric_limits<float>::max(),
  };

  glm::vec3 voxelBoundary{
      rayDirection.x > 0 ? voxel.x + 0.5f : voxel.x - 0.5f,
      rayDirection.y > 0 ? voxel.y + 0.5f : voxel.y - 0.5f,
      rayDirection.z > 0 ? voxel.z + 0.5f : voxel.z - 0.5f,
  };

  glm::vec3 tMax{
      rayDirection.x != 0.0f ? (voxelBoundary.x - origin.x) / rayDirection.x
                             : std::numeric_limits<float>::max(),
      rayDirection.y != 0.0f ? (voxelBoundary.y - origin.y) / rayDirection.y
                             : std::numeric_limits<float>::max(),
      rayDirection.z != 0.0f ? (voxelBoundary.z - origin.z) / rayDirection.z
                             : std::numeric_limits<float>::max(),
  };

  glm::ivec3 hitFace(0);
  float traveled = 0.0f;

  while (traveled <= reach) {
    if (collision(glm::vec3(voxel) + halfBlock)) {
      return (ray::Intersection){
          glm::vec3(voxel) + halfBlock,
          hitFace,
      };
    }

    if (tMax.x < tMax.y) {
      if (tMax.x < tMax.z) {
        voxel.x += step.x;
        traveled = tMax.x;
        tMax.x += tDelta.x;
        hitFace = step.x > 0 ? DIRECTIONS[WEST] : DIRECTIONS[EAST];
      } else {
        voxel.z += step.z;
        traveled = tMax.z;
        tMax.z += tDelta.z;
        hitFace = step.z > 0 ? DIRECTIONS[NORTH] : DIRECTIONS[SOUTH];
      }
    } else {
      if (tMax.y < tMax.z) {
        voxel.y += step.y;
        traveled = tMax.y;
        tMax.y += tDelta.y;
        hitFace = step.y > 0 ? DIRECTIONS[DOWN] : DIRECTIONS[TOP];
      } else {
        voxel.z += step.z;
        traveled = tMax.z;
        tMax.z += tDelta.z;
        hitFace = step.z > 0 ? DIRECTIONS[NORTH] : DIRECTIONS[SOUTH];
      }
    }
  }

  return std::nullopt;
}
