#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "../state.hpp"
#include "../utils/vectors.hpp"
#include "gfx.hpp"
#include "glad/glad.h"
#include "shader.hpp"

struct Vertex {
  glm::vec3 Position;
  glm::ivec3 FaceDirection;
  glm::vec2 TexCoords;
};

enum class RenderType { NORMAL = 0, TRANSPARENT };

static std::vector<unsigned int> vertexSizes{3, 3, 2};

/** VertexBuffer */
class VertexBuffer {
private:
  unsigned int id;

public:
  VertexBuffer(const void *data, unsigned int size);
  ~VertexBuffer();

  void bind() const;
  void unbind() const;
};

/** IndexBuffer */
class IndexBuffer {
private:
  unsigned int id;
  unsigned int m_count;

public:
  IndexBuffer(const void *data, unsigned int count);
  ~IndexBuffer();

  void bind() const;
  void unbind() const;
  unsigned int get_count() const {
    return m_count;
  }
};

/** Primitive */
class Primitive {
private:
  unsigned int VAO;
  VertexBuffer *vb;
  IndexBuffer *ib;

  std::vector<Vertex> vertices;
  std::map<RenderType, std::vector<unsigned int>> indices_map;
  std::map<RenderType, IndexBuffer *> ib_map;

  int n_faces = 0;

public:
  Primitive();
  ~Primitive();

  void clean();
  void prepare();
  void draw(const glm::vec3 &position, Shader *shader, const Texture &texture);
  void push(const std::vector<Vertex> &v, std::vector<unsigned int> _indices,
            RenderType render_type);
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

  std::vector<glm::vec3> vertices() const {
    return CUBE_VERTICES[direction];
  }
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
