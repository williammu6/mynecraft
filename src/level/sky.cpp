#include "sky.hpp"

void Sky::prepare_render() {
  glm::vec3 p = state.sun_position;
  auto vertices = get_block_vertices();
  std::vector<Vertex> real_vertices;
  std::vector<unsigned int> indices;

  for (CubeFace c : CUBE_FACES) {
    std::vector<glm::vec3> V = c.vertices();

    auto face_direction = DIRECTIONS[c.direction];

    real_vertices.push_back(
        {V[0] * c.position + p, face_direction, glm::vec2(0, 0)});
    real_vertices.push_back(
        {V[1] * c.position + p, face_direction, glm::vec2(0, 1)});
    real_vertices.push_back(
        {V[2] * c.position + p, face_direction, glm::vec2(1, 0)});
    real_vertices.push_back(
        {V[3] * c.position + p, face_direction, glm::vec2(1, 1)});

    // this->indices.push_back(QUAD_FACE_INDICES[cube_face.direction]);

    for (auto i : QUAD_FACE_INDICES[c.direction]) {
      indices.push_back(i);
    }
  }

  // for (auto v : vertices) { real_vertices.push_back( {v * this->position,
  // glm::vec3(1, 0, 0), glm::vec2(0, 0)}); }
  primitive->prepare(real_vertices, indices);
}

void Sky::render() {
  Shader *shader = state.renderer->sun_shader;

  glm::vec3 p = state.sun_position;

  float r = glm::radians(-45.0f);

  auto setup_model = [&shader, &p, &r]() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(state.camera.model, p);
    model = glm::scale(model, glm::vec3(25.0f));
    model =
        glm::rotate(model, r * state.tick, glm::vec3({1, 0, 0}));
    model = glm::rotate(model, 0.0f, glm::vec3({0, 1, 0}));
    model = glm::rotate(model, 0.0f, glm::vec3({0, 0, 1}));
    shader->setMat4("model", model);
  };

  printf("Pos %f %f %f\n", p.x, p.y, p.z);
  printf("Camera %f %f %f\n", state.camera.position.x, state.camera.position.y,
         state.camera.position.z);

  primitive->draw(p, shader, state.renderer->textures[TextureID::SUN],
                  setup_model);
}
