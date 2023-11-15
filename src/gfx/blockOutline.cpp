#include "blockOutline.hpp"

void BlockOutline::setup() {
  primitive->reset();

  for (const auto &cubeFace : CUBE_FACES) {
    std::vector<Vertex> vertices;

    std::vector<glm::vec3> V = cubeFace.vertices();

    for (int i = 0; i < 4; i++) {
      vertices.push_back({.Position = V[i] * cubeFace.position,
                          .FaceDirection = DIRECTIONS[cubeFace.direction],
                          .TexCoords = glm::vec2(0)});
    }
    primitive->push(vertices, QUAD_FACE_INDICES[cubeFace.direction],
                    RenderType::NORMAL);
  }

  this->primitive->prepare();
}
