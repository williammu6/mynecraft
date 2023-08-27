#pragma once

#include "../common.hpp"
#include "../gfx/gfx.hpp"
#include "../state.hpp"

struct Vertex {
  glm::vec3 Position;
  glm::vec3 FaceDirection;
  glm::vec2 TexCoords;
};

class Mesh {
public:
  std::vector<std::vector<Vertex>> vertices;
  std::vector<std::vector<unsigned int>> indices;

  Mesh(std::vector<std::vector<Vertex>> vertices,
       std::vector<std::vector<unsigned int>> indices);

  ~Mesh() {
    this->vertices.clear();
    this->vertices.shrink_to_fit();
    this->indices.clear();
    this->indices.shrink_to_fit();
  }

  void draw(glm::vec3 position, struct Texture *texture);

private:
  unsigned int VAO, VBO, EBO;
  void setup();
};
