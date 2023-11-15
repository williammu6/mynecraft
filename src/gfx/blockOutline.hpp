#ifndef BLOCK_OUTLINE_H
#define BLOCK_OUTLINE_H

#include "../common.hpp"
#include "../state.hpp"
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

  void setup(glm::vec3 position);

private:
  std::unique_ptr<Primitive> primitive;
};

#endif
