#include "sky.hpp"

void Sky::prepare_render() {
  glm::vec3 p = state.sun_position;
  auto vertices = get_block_vertices();
  std::vector<Vertex> real_vertices;
  std::vector<unsigned int> indices;

  for (CubeFace c : CUBE_FACES) {
    std::vector<glm::vec3> V = c.vertices();

    auto face_direction = DIRECTIONS[c.direction];

    real_vertices.push_back({V[0] * c.position + p, face_direction, glm::vec2(0, 0)});
    real_vertices.push_back({V[1] * c.position + p, face_direction, glm::vec2(0, 1)});
    real_vertices.push_back({V[2] * c.position + p, face_direction, glm::vec2(1, 0)});
    real_vertices.push_back({V[3] * c.position + p, face_direction, glm::vec2(1, 1)});

    for (auto i : QUAD_FACE_INDICES[c.direction]) {
      indices.push_back(i);
    }
  }

  primitive->prepare(real_vertices, indices);
}

void Sky::render() {
  // primitive->draw(state.sun_position, state.renderer->sky_shader, state.renderer->textures[TextureID::SUN]);
}
