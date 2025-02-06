#include "block_outline.hpp"
#include "../state.hpp"

void BlockOutline::draw(glm::vec3 position) {
  mesh->drawOpaque(glm::round(position - 0.5f),
                   state.renderer->shaders[Shaders::BLOCK_OUTLINE]);
}

void BlockOutline::setup() {
  mesh->reset();

  std::vector<glm::vec2> empty(4, glm::vec2(0));

  for (const auto &cubeFace : CUBE_FACES) {
    const std::vector<VertexType> vertices =
        cubeFace.blockVertex(glm::vec3(0), empty, 1.0f);

    mesh->push(vertices, QUAD_FACE_INDICES[cubeFace.direction],
               RenderType::NORMAL);
  }

  mesh->addVertexBuffer({positionAttrib, uvAttrib});
};
