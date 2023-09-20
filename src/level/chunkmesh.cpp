#include "chunkmesh.hpp"

void ChunkMesh::setup() {
  std::vector<Vertex> all_vertices;
  std::vector<unsigned int> all_indices;

  for (auto vertex : vertices)
    all_vertices.insert(all_vertices.end(), vertex.begin(), vertex.end());

  for (int index = 0; index < indices.size(); index++) {
    for (auto in : indices[index]) {
      all_indices.push_back(in + index * 4);
    }
  }

  primitive->prepare(all_vertices, all_indices);
}

void ChunkMesh::draw(glm::vec3 position, struct Texture *texture) {
  Shader *shader = state.renderer->shader;

  auto setup_shader = [&shader, &position]() {
    shader->setVec3("light.position", state.sun_position);
    shader->setVec3("viewPos", state.camera.position);

    shader->setInt("material.diffuse", 0);
    shader->setInt("material.specular", 1);
    shader->setFloat("material.shininess", 32.0f);

    shader->setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    shader->setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    shader->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

    shader->setFloat("light.constant", state.sun_position.y < 0 ? 5.0f : 0.5f);
    shader->setFloat("light.linear", 0.09f);
    shader->setFloat("light.quadratic", 0.32f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(state.camera.model, position);
    shader->setMat4("model", model);
  };

  primitive->draw(position, shader, *texture, setup_shader);
}

void ChunkMesh::add_face(CubeFace cube_face, glm::ivec3 position,
                         glm::vec2 texture_offset) {
  Texture texture = state.renderer->textures[TextureID::ATLAS];

  auto face_direction = DIRECTIONS[cube_face.direction];

  float minTX = texture.tile_size * texture_offset.x / texture.width;

  float maxTX = texture.tile_size * (texture_offset.x + 1) / texture.width;

  float minTY = texture.tile_size * texture_offset.y / texture.height;

  float maxTY = texture.tile_size * (texture_offset.y + 1) / texture.height;

  std::vector<glm::vec3> V = cube_face.vertices();
  glm::vec3 float_position = position;

  this->vertices.push_back({{V[0] * cube_face.position + float_position,
                             face_direction, glm::vec2(minTX, minTY)},
                            {V[1] * cube_face.position + float_position,
                             face_direction, glm::vec2(maxTX, minTY)},
                            {V[2] * cube_face.position + float_position,
                             face_direction, glm::vec2(minTX, maxTY)},
                            {V[3] * cube_face.position + float_position,
                             face_direction, glm::vec2(maxTX, maxTY)}});

  this->indices.push_back(QUAD_FACE_INDICES[cube_face.direction]);
}
