#include "chunkmesh.hpp"

void ChunkMesh::setup() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  std::vector<Vertex> all_vertices;
  std::vector<unsigned int> all_indices;

  for (auto vertex : vertices)
    all_vertices.insert(all_vertices.end(), vertex.begin(), vertex.end());

  for (int index = 0; index < indices.size(); index++) {
    for (auto in : indices[index]) {
      all_indices.push_back(in + index * 4);
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, 4 * vertices.size() * sizeof(Vertex),
               &all_vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               all_indices.size() * sizeof(unsigned int), &all_indices[0],
               GL_STATIC_DRAW);

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Face direction
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Texture Coords
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);
}

void ChunkMesh::draw(glm::vec3 position, struct Texture *texture) {
  Shader *shader = state.renderer->shader;
  shader->use();

  // printf("Camera %.2f %.2f %.2f\n", state.camera.position.x,
  // state.camera.position.y, state.camera.position.z);
  // shader->setVec3("light.position", state.camera.position);
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

  glBindVertexArray(VAO);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(state.camera.model, position);

  shader->setMat4("view", state.camera.view);
  shader->setMat4("model", model);
  shader->setMat4("projection", state.camera.projection);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture->texture);

  glDrawElements(GL_TRIANGLES, indices.size() * 6, GL_UNSIGNED_INT, (void *)0);
}

void ChunkMesh::add_face(CubeFace cube_face, glm::vec3 position,
                         glm::vec2 texture_offset) {
  Texture texture = state.renderer->textures[TextureID::ATLAS];

  auto face_direction = DIRECTIONS[cube_face.direction];

  float minTX = texture.tile_size * texture_offset.x / texture.width;

  float maxTX = texture.tile_size * (texture_offset.x + 1) / texture.width;

  float minTY = texture.tile_size * texture_offset.y / texture.height;

  float maxTY = texture.tile_size * (texture_offset.y + 1) / texture.height;

  glm::vec3 *V = cube_face.vertices();

  std::vector<Vertex> tmp_vertices;

  this->vertices.push_back({{V[0] * cube_face.position + position,
                             face_direction, glm::vec2(minTX, minTY)},
                            {V[1] * cube_face.position + position,
                             face_direction, glm::vec2(maxTX, minTY)},
                            {V[2] * cube_face.position + position,
                             face_direction, glm::vec2(minTX, maxTY)},
                            {V[3] * cube_face.position + position,
                             face_direction, glm::vec2(maxTX, maxTY)}});

  this->indices.push_back(QUAD_FACE_INDICES[cube_face.direction]);
}
