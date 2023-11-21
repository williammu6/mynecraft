#ifndef RAY_H
#define RAY_H

#include "../gfx/direction.hpp"
#include "../scene/blocks/block.hpp"
#include "../scene/world.hpp"
#include "../state.hpp"
#include "glm/glm.hpp"
#include <optional>

struct Intersection {
  glm::vec3 position;
  glm::ivec3 blockPosition;
  std::optional<Chunk *> placeBlockChunk;
  glm::ivec3 placeBlockPosition;
};

struct Ray {
  std::optional<Intersection> intersection(const struct World &world,
                                           float reach);

  glm::vec3 origin;
  glm::vec3 direction;
};

#endif
