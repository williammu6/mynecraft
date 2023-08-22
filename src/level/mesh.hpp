#pragma once

#include "../gfx/gfx.hpp"
#include "../common.hpp"
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
  void draw(glm::vec3 position);

private:
  unsigned int VAO, VBO, EBO;
  void setup();
};
