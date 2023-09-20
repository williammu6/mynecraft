#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "../state.hpp"
#include "../utils/vectors.hpp"
#include "gfx.hpp"
#include "glad/glad.h"
#include "shader.hpp"

struct Vertex {
  glm::vec3 Position;
  glm::vec3 FaceDirection;
  glm::vec2 TexCoords;
};

class Primitive {
private:
  unsigned int VAO, VBO, EBO;

public:
  Primitive() { n_indices = 0; };
  ~Primitive(){
      // glDeleteVertexArrays(VAO);
      // glDeleteBuffers(VBO);
  };

  int n_indices;

  template <class T>
  void prepare(std::vector<T> vertices, std::vector<unsigned int> indices) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * vertices.size() * sizeof(T), &vertices[0],
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)0);
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

    n_indices += indices.size();
  }

  void draw(glm::vec3 position, Shader *shader, Texture texture,
            std::function<void()> fn) {
    shader->use();

    glBindVertexArray(VAO);

    fn();
    shader->setMat4("view", state.camera.view);
    shader->setMat4("projection", state.camera.projection);

    glActiveTexture(GL_TEXTURE + (int)texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.pixels);

    glDrawElements(GL_TRIANGLES, n_indices * 6, GL_UNSIGNED_INT, (void *)0);

    glBindVertexArray(0);
  }
};

static std::vector<glm::vec3> CUBE_F_B_VERTICES = {
    glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.5, -0.5, 0.5),
    glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5)};

static std::vector<glm::vec3> CUBE_L_R_VERTICES = {
    glm::vec3(-0.5, -0.5, -0.5), glm::vec3(-0.5, 0.5, -0.5),
    glm::vec3(-0.5, -0.5, 0.5), glm::vec3(-0.5, 0.5, 0.5)};

static std::vector<glm::vec3> CUBE_T_B_VERTICES = {
    glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.5, 0.5, -0.5),
    glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5)};

static std::vector<std::vector<unsigned int>> QUAD_FACE_INDICES{
    {2, 1, 0, 1, 2, 3}, {0, 1, 2, 1, 3, 2}, {0, 1, 2, 1, 3, 2},
    {2, 1, 0, 2, 3, 1}, {2, 1, 0, 2, 3, 1}, {0, 1, 2, 3, 2, 1},
};

static std::vector<std::vector<glm::vec3>> CUBE_VERTICES{
    CUBE_T_B_VERTICES, // TOP
    CUBE_F_B_VERTICES, // SOUTH
    CUBE_L_R_VERTICES, // WEST
    CUBE_L_R_VERTICES, // EAST
    CUBE_F_B_VERTICES, // NORTH
    CUBE_T_B_VERTICES  // DOWN
};

static std::vector<glm::vec3> get_block_vertices() {
  return flatten(CUBE_VERTICES);
}

static std::vector<unsigned int> get_block_indices() {
  return flatten(QUAD_FACE_INDICES);
}

struct CubeFace {
  enum Direction direction;
  glm::vec3 position;

  std::vector<glm::vec3> vertices() { return CUBE_VERTICES[direction]; }
};

const glm::ivec3 DIRECTIONS[] = {glm::ivec3(0, 1, 0),  glm::ivec3(0, 0, 1),
                                 glm::ivec3(-1, 0, 0), glm::ivec3(1, 0, 0),
                                 glm::ivec3(0, 0, -1), glm::ivec3(0, -1, 0)};

static const std::vector<CubeFace> CUBE_FACES{
    {TOP, glm::vec3(1, 1, 1)},    {SOUTH, glm::vec3(1, 1, 1)},
    {EAST, glm::vec3(1, 1, 1)},   {WEST, glm::vec3(-1, 1, 1)},
    {NORTH, glm::vec3(1, 1, -1)}, {DOWN, glm::vec3(1, -1, 1)},
};

#endif
