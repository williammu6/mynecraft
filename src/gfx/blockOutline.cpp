#include "blockOutline.hpp"

void BlockOutline::setup(glm::vec3 position) {
  primitive->reset();

  for (const auto &cubeFace : CUBE_FACES) {
    std::vector<Vertex> vertices;

    CubeFace realCubeFace = CUBE_FACES[cubeFace.direction];
    std::vector<glm::vec3> V = realCubeFace.vertices();
    for (int i = 0; i < 4; i++) {
      vertices.push_back({.Position = V[i] * realCubeFace.position,
                          .FaceDirection = DIRECTIONS[realCubeFace.direction],
                          .TexCoords = glm::vec2(0)});
    }
    printf("Adding %zu\n", vertices.size());
    primitive->push(vertices, QUAD_FACE_INDICES[realCubeFace.direction],
                    RenderType::NORMAL);
  }

  this->primitive->prepare();
}
