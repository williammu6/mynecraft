#pragma once

// #include "../common.hpp"

#include "../gfx/gfx.hpp"
#include <iostream>
#include <tuple>
#include <unordered_map>

// Specialize std::hash for your custom key type
namespace std {
template <> struct hash<glm::ivec3> {
  size_t operator()(const glm::ivec3 &p) const {
    size_t seed = 0;
    seed ^= hash<int>{}(p.x) + 0x9e3779b9 + (seed << 3) + (seed >> 2);
    seed ^= hash<int>{}(p.y) + 0x9e3779b9 + (seed << 3) + (seed >> 2);
    seed ^= hash<int>{}(p.z) + 0x9e3779b9 + (seed << 3) + (seed >> 2);
    return seed;
  }
};
} // namespace std
