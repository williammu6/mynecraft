#ifndef AABB_H
#define AABB_H

#include "../common.hpp"
#include "../gfx/gfx.hpp"
#include "../utils/debug.hpp"

struct AABB {
  glm::vec3 min;
  glm::vec3 max;

  bool intersects(AABB other) {
    return (min.x <= other.max.x && max.x >= other.min.x) &&
           (min.y <= other.max.y && max.y >= other.min.y) &&
           (min.z <= other.max.z && max.z >= other.min.z);
  }
};

#endif
