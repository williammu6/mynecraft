#include "mesh.hpp"

Mesh::Mesh(std::vector<std::vector<Vertex>> vertices,
           std::vector<std::vector<unsigned int>> indices) {
  this->vertices = vertices;
  this->indices = indices;

  setupMesh();
}

void Mesh::setupMesh() {
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

void Mesh::draw(glm::vec3 position) {
  Shader *shader = state.renderer->shader;
  shader->use();

  shader->setInt("material.diffuse", 0);
  shader->setInt("material.specular", 1);

  shader->setMat4("view", state.camera.view);
  shader->setMat4("projection", state.camera.projection);

  shader->setVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
  shader->setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
  shader->setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
  shader->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

  /*
  shader->>setVec3("lightPos", state.sun_position);
  shader->>setVec3("viewPos", state.sun_position);
  shader->>setVec3("lightColor", glm::vec3(255, 100, 100));
  */

  // shader->>setVec3("view", state.sun_position);

  glBindVertexArray(VAO);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(state.camera.model, position);

  shader->setMat4("model", model);
  shader->setMat4("view", state.camera.view);
  shader->setMat4("projection", state.camera.projection);

  glDrawElements(GL_TRIANGLES, indices.size() * 6, GL_UNSIGNED_INT, (void *)0);
}
