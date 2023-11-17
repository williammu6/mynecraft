#ifndef BLOCK_OUTLINE_H
#define BLOCK_OUTLINE_H

#include "../common.hpp"
#include "../scene/world.hpp"
#include "./primitive.hpp"

class BlockOutline {
public:
  BlockOutline() {
    primitive = std::make_unique<Primitive>();
  }

  void draw(glm::vec3 position) {
    primitive->drawOpaque(position,
                          state.renderer->shaders[Shaders::BLOCK_OUTLINE]);
  }

  void setup();

private:
  std::unique_ptr<Primitive> primitive;
};

#endif
