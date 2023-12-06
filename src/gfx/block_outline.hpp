#ifndef BLOCK_OUTLINE_H
#define BLOCK_OUTLINE_H

#include "Mesh/mesh.hpp"

class BlockOutline {
public:
  using VertexType = CubeVertex;

  BlockOutline() {
    mesh = std::make_unique<Mesh<VertexType>>();
  }

  void draw(glm::vec3 position);
  void setup();

private:
  std::unique_ptr<Mesh<VertexType>> mesh;
};

#endif
