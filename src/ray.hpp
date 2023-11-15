#ifndef RAY_H
#define RAY_H

#include "gfx/direction.hpp"
#include "glm/glm.hpp"
#include "level/blocks/block.hpp"
#include "level/world.hpp"
#include "state.hpp"
#include <optional>

struct Intersection {
  glm::vec3 position;
  glm::ivec3 faceDirection;
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
