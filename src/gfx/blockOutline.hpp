#ifndef BLOCK_OUTLINE_H
#define BLOCK_OUTLINE_H

#include "../state.hpp"
#include "Mesh/mesh.hpp"

class BlockOutline {
public:
  using VertexType = CubeVertex;

  BlockOutline() {
    mesh = std::make_unique<Mesh<VertexType>>();
  }

  void draw(glm::vec3 position) {
    mesh->drawOpaque(glm::round(position - 0.5f),
                     state.renderer->shaders[Shaders::BLOCK_OUTLINE]);
  }

  void setup() {
    mesh->reset();

    std::vector<glm::vec2> empty(4, glm::vec2(0));

    for (const auto &cubeFace : CUBE_FACES) {
      const std::vector<VertexType> vertices =
          cubeFace.blockVertex(glm::vec3(0), empty);

      mesh->push(vertices, QUAD_FACE_INDICES[cubeFace.direction],
                 RenderType::NORMAL);
    }

    mesh->addVertexBuffer({positionAttrib, uvAttrib});
  };

private:
  std::unique_ptr<Mesh<VertexType>> mesh;
};

#endif
