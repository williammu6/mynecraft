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
  std::optional<Chunk *>placeBlockChunk;
  glm::ivec3 placeBlockPosition;
};

class Ray {
public:
  Ray(){};
  ~Ray(){};
  void setOrigin(glm::vec3 origin) {
    _origin = origin;
  };
  void setDirection(glm::vec3 direction) {
    _direction = direction;
  };
  std::optional<Intersection> intersection(const struct World &world,
                                           float reach);

private:
  glm::vec3 _origin;
  glm::vec3 _direction;
};

#endif
