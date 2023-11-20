#ifndef AABB_H
#define AABB_H

struct AABB {
  float minX, maxX, minY, maxY, minZ, maxZ;

  bool intersects(AABB other) {
    return (minX <= other.maxX && maxX >= other.minX) &&
           (minY <= other.maxY && maxY >= other.minY) &&
           (minZ <= other.maxZ && maxZ >= other.minZ);
  }
};

#endif
