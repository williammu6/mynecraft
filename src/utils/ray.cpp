#include "ray.hpp"

struct AxisInfo {
  glm::vec3 step;
  glm::ivec3 faceSide;
};

std::optional<ray::Intersection>
ray::cast(glm::vec3 origin, glm::vec3 direction,
          std::function<bool(const glm::vec3 &)> collision, float reach) {
  if (direction == glm::vec3(0))
    return std::nullopt;

  glm::vec3 rayPosition = origin;
  float halfBlock = 0.5f;
  glm::vec3 stepSize = direction / 5.0f;

  std::vector<AxisInfo> stepAxis{
      {glm::vec3(0, 0, stepSize.z),
       direction.z < 0 ? DIRECTIONS[SOUTH] : DIRECTIONS[NORTH]},
      {glm::vec3(stepSize.x, 0, 0),
       direction.x < 0 ? DIRECTIONS[EAST] : DIRECTIONS[WEST]},
      {glm::vec3(0, stepSize.y, 0),
       direction.y < 0 ? DIRECTIONS[TOP] : DIRECTIONS[DOWN]}};

  while (glm::abs(glm::distance(origin, rayPosition)) <= reach) {
    for (const auto &axisInfo : stepAxis) {
      rayPosition += axisInfo.step;

      if (collision(rayPosition + halfBlock)) {
        return (ray::Intersection){
            rayPosition + halfBlock,
            axisInfo.faceSide,
        };
      }
    }
  }

  return std::nullopt;
}
