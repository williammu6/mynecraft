#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include "../common.hpp"
#include "../gfx/gfx.hpp"
#include "../state.hpp"

static glm::vec3 CUBE_F_B_VERTICES[] = {
    glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.5, -0.5, 0.5),
    glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5)};

static glm::vec3 CUBE_L_R_VERTICES[] = {
    glm::vec3(-0.5, -0.5, -0.5), glm::vec3(-0.5, 0.5, -0.5),
    glm::vec3(-0.5, -0.5, 0.5), glm::vec3(-0.5, 0.5, 0.5)};

static glm::vec3 CUBE_T_B_VERTICES[] = {
    glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.5, 0.5, -0.5),
    glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5)};

static std::vector<std::vector<unsigned int>> QUAD_FACE_INDICES{
    {2, 1, 0, 1, 2, 3}, {0, 1, 2, 1, 3, 2}, {0, 1, 2, 1, 3, 2},
    {2, 1, 0, 2, 3, 1}, {2, 1, 0, 2, 3, 1}, {0, 1, 2, 3, 2, 1},
};

struct CubeFace {
  enum Direction direction;
  glm::vec3 position;

  glm::vec3 *vertices() {
    switch (direction) {
    case TOP:
      return CUBE_T_B_VERTICES;
    case NORTH:
    case SOUTH:
      return CUBE_F_B_VERTICES;
    case WEST:
    case EAST:
      return CUBE_L_R_VERTICES;
    case DOWN:
      return CUBE_T_B_VERTICES;
    }
  }
};

const glm::vec3 DIRECTIONS[] = {glm::vec3(0, 1, 0),  glm::vec3(0, 0, 1),
                                glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0),
                                glm::vec3(0, 0, -1), glm::vec3(0, -1, 0)};

static const std::vector<CubeFace> CUBE_FACES{
    {TOP, glm::vec3(1, 1, 1)},    {SOUTH, glm::vec3(1, 1, 1)},
    {EAST, glm::vec3(1, 1, 1)},   {WEST, glm::vec3(-1, 1, 1)},
    {NORTH, glm::vec3(1, 1, -1)}, {DOWN, glm::vec3(1, -1, 1)},
};

struct Vertex {
  glm::vec3 Position;
  glm::vec3 FaceDirection;
  glm::vec2 TexCoords;
};

class ChunkMesh {
public:
  ChunkMesh() {
    this->indices = {};
    this->vertices = {};
  };
  ~ChunkMesh() { clean(); }

  void draw(glm::vec3 position, struct Texture *texture);
  void add_face(CubeFace cube_face, glm::vec3 position,
                glm::vec2 texture_offset);
  void setup();
  void clean() {
    this->vertices.clear();
    this->vertices.shrink_to_fit();
    this->indices.clear();
    this->indices.shrink_to_fit();
  }

private:
  unsigned int VAO, VBO, EBO;

  std::vector<std::vector<Vertex>> vertices;
  std::vector<std::vector<unsigned int>> indices;
};

#endif
