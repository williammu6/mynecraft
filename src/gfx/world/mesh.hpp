#pragma once

#include "../../common.hpp"
#include "../../state.hpp"
#include "../gfx.hpp"
#include "../shader.hpp"

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
