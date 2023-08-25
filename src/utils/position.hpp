#pragma once

#include "../common.hpp"

struct Position {
  int x;
  int y;
  int z;

  bool operator==(const Position position) const {
    return position.x == x && position.y == y && position.z == z;
  }

  struct Hash {
    std::size_t operator()(const Position &p) const {
      std::hash<int> hasher;
      return hasher(p.x) ^ hasher(p.z);
    }
  };
};
