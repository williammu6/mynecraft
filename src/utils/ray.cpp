#include "ray.hpp"

struct AxisInfo {
  glm::vec3 step;
  glm::ivec3 faceSide;
};

std::optional<ray::Intersection>
ray::cast(glm::vec3 origin,
          glm::vec3 direction,
          std::function<bool(const glm::vec3 &)> collision,
          float reach) {
  if (glm::length(direction) < 1e-5f) // Handle nearly zero directions
    return std::nullopt;

  glm::vec3 rayPosition = origin;
  glm::vec3 stepSize =
      glm::normalize(direction) * 0.1f; // Adjust step size to suit your needs
  glm::vec3 nextBoundary = origin;

  // Axis information with step size and face direction
  std::vector<AxisInfo> stepAxis{
      {glm::vec3(0, 0, stepSize.z),
       direction.z < 0 ? DIRECTIONS[SOUTH] : DIRECTIONS[NORTH]},
      {glm::vec3(stepSize.x, 0, 0),
       direction.x < 0 ? DIRECTIONS[EAST] : DIRECTIONS[WEST]},
      {glm::vec3(0, stepSize.y, 0),
       direction.y < 0 ? DIRECTIONS[TOP] : DIRECTIONS[DOWN]}};

  // Use distance traveled instead of Euclidean distance to simplify
  float distanceTraveled = 0;

  while (distanceTraveled <= reach) {
    // Calculate which axis to step based on the smallest distance to the next boundary
    glm::vec3 directionToBoundary = nextBoundary - rayPosition;
    float minDist = glm::length(directionToBoundary);

    // Check each axis and pick the closest one
    for (const auto &axisInfo : stepAxis) {
      rayPosition += axisInfo.step;
      if (collision(rayPosition + 0.5f)) { // Half-block offset
        return ray::Intersection{rayPosition + 0.5f, axisInfo.faceSide};
      }
    }

    // Increment the distance traveled and step forward
    distanceTraveled += glm::length(stepSize);
  }

  return std::nullopt;
}
