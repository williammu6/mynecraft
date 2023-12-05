#ifndef POSITION_H
#define POSITION_H

#include <glm/glm.hpp>
#include <functional>

namespace std {
template <> struct hash<glm::ivec3> {
  size_t operator()(const glm::ivec3 &p) const {
    std::size_t hash = 17; // A prime number to start with
    hash = hash * 31 + static_cast<std::size_t>(p.x);
    hash = hash * 31 + static_cast<std::size_t>(p.y);
    hash = hash * 31 + static_cast<std::size_t>(p.z);
    return hash;
  }
};
} // namespace std

#endif
