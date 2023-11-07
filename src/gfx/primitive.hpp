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

struct VertexAttrib {
  GLenum type;
  GLint size;
  GLboolean normalized;
};

static const std::vector<VertexAttrib> vertex_attribs{
    {GL_FLOAT, 3, GL_FALSE}, // Position
    {GL_FLOAT, 3, GL_FALSE}, // Normal
    {GL_FLOAT, 2, GL_FALSE}, // Texture
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
  std::unique_ptr<VertexBuffer> vb;

  std::vector<Vertex> vertices{};
  std::map<RenderType, std::vector<unsigned int>> indices_map;
  std::map<RenderType, std::unique_ptr<IndexBuffer>> ib_map;

  int n_faces = 0;

public:
  Primitive() {
    glGenVertexArrays(1, &VAO);
  }
  ~Primitive() {
    glDeleteVertexArrays(1, &VAO);
    indices_map.clear();
    ib_map.clear();
    vertices.clear();
    vertices.shrink_to_fit();
  }

  void prepare() {
    vb = std::make_unique<VertexBuffer>(static_cast<void *>(vertices.data()),
                                        4 * vertices.size() * sizeof(Vertex));

    glBindVertexArray(VAO);
    vb->bind();

    for (const auto type : {RenderType::NORMAL, RenderType::TRANSPARENT}) {
      ib_map[type] = std::make_unique<IndexBuffer>(
          static_cast<void *>(indices_map[type].data()),
          indices_map[type].size());

      for (int vertex_idx = 0; vertex_idx < vertex_attribs.size();
           vertex_idx++) {
        VertexAttrib vertex_attrib = vertex_attribs[vertex_idx];
        glVertexAttribPointer(vertex_idx, vertex_attrib.size,
                              vertex_attrib.type, vertex_attrib.normalized,
                              8 * sizeof(float),
                              (void *)(vertex_idx * 3 * sizeof(float)));
        glEnableVertexAttribArray(vertex_idx);
      }
    }
  };

  void draw(const glm::vec3 &position, Shader *shader, const Texture &texture) {
    shader->use();
    shader->setUniforms(position);
    glActiveTexture(GL_TEXTURE + (int)texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.pixels);

    glBindVertexArray(VAO);
    vb->bind();

    for (const auto type : {RenderType::NORMAL, RenderType::TRANSPARENT}) {
      if (indices_map[type].size() == 0)
        continue;
      ib_map[type]->bind();
      shader->setUniform("material.opacity",
                         type == RenderType::TRANSPARENT ? 0.6f : 1.0f);
      glDrawElements(GL_TRIANGLES, indices_map[type].size(), GL_UNSIGNED_INT,
                     (void *)0);
    }
  };

  void push(const std::vector<Vertex> &v, std::vector<unsigned int> _indices,
            RenderType render_type) {
    vertices.insert(vertices.end(), v.begin(), v.end());
    for (auto i : _indices)
      indices_map[render_type].push_back(i + n_faces * 4);
    n_faces++;
  };
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
