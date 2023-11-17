#include "blockOutline.hpp"

void BlockOutline::setup() {
  primitive->reset();

  std::vector<glm::vec2> empty(4, glm::vec2(0));

  for (const auto &cubeFace : CUBE_FACES) {
    const std::vector<VertexType> vertices =
        cubeFace.blockVertex(glm::vec3(0), empty);

    primitive->push(vertices, QUAD_FACE_INDICES[cubeFace.direction],
                    RenderType::NORMAL);
  }

  this->primitive->prepare();
}
