#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "../state.hpp"
#include "../utils/vectors.hpp"
#include "gfx.hpp"
#include "glad/glad.h"
#include "shader.hpp"

struct CubeVertex {
  glm::vec3 Position;
  glm::ivec3 Normal;
  glm::vec2 uv;
};

struct PlainTextureVertex {
  glm::vec3 Position;
  glm::vec2 uv;
};

struct VertexAttrib {
  GLenum type;
  GLint size;
  GLboolean normalized;
};

static const std::vector<VertexAttrib> vertex_attribs{
    {GL_FLOAT, 3, GL_FALSE}, // Position
    {GL_FLOAT, 3, GL_FALSE}, // Normal
    {GL_FLOAT, 2, GL_FALSE}, // uv
};

static const std::vector<VertexAttrib> vertex_attribs_plain{
    {GL_FLOAT, 3, GL_FALSE}, // Position
    {GL_FLOAT, 2, GL_FALSE}, // uv
};

enum class RenderType { NORMAL = 0, TRANSPARENT };

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
template <typename T> class Primitive {
private:
  unsigned int VAO;
  std::unique_ptr<VertexBuffer> vb;

  std::vector<T> vertices;
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

  void prepare();

  void addVertexBuffer(const std::vector<VertexAttrib> & attributes);

  void draw(const glm::vec3 &position, Shader *shader, const Texture &texture) {
    shader->use();
    shader->setUniforms(position);
    glActiveTexture(GL_TEXTURE + static_cast<int>(texture.id));
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

  void drawOpaque(const glm::vec3 &position, Shader *shader) {
    RenderType type = RenderType::NORMAL;
    shader->use();
    shader->setUniforms(position);
    glBindVertexArray(VAO);
    vb->bind();
    ib_map[type]->bind();
    glDrawElements(GL_TRIANGLES, indices_map[type].size(), GL_UNSIGNED_INT,
                   (void *)0);
  }

  void push(const std::vector<T> &v, std::vector<unsigned int> _indices,
            RenderType render_type) {
    vertices.insert(vertices.end(), v.begin(), v.end());
    for (auto i : _indices)
      indices_map[render_type].push_back(i + n_faces * 4);
    n_faces++;
  };

  void reset() {
    vertices.erase(vertices.begin(), vertices.end());
    vertices.shrink_to_fit();
  }
};

static std::vector<glm::vec3> CUBE_F_B_VERTICES = {
    {-0.5, -0.5, 0.5}, {0.5, -0.5, 0.5}, {-0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}};

static std::vector<glm::vec3> CUBE_L_R_VERTICES = {
    {-0.5, -0.5, -0.5}, {-0.5, 0.5, -0.5}, {-0.5, -0.5, 0.5}, {-0.5, 0.5, 0.5}};

static std::vector<glm::vec3> CUBE_T_B_VERTICES = {
    {-0.5, 0.5, -0.5}, {0.5, 0.5, -0.5}, {-0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}};

static std::vector<std::vector<unsigned int>> QUAD_FACE_INDICES{
    {2, 1, 0, 1, 2, 3}, {0, 1, 2, 1, 3, 2}, {0, 1, 2, 1, 3, 2},
    {2, 1, 0, 2, 3, 1}, {2, 1, 0, 2, 3, 1}, {0, 1, 2, 3, 2, 1},
};

inline std::vector<glm::vec3> getVerticesByFaceDirection(enum Direction face) {
  switch (face) {
  case TOP:
  case DOWN:
    return CUBE_T_B_VERTICES;
  case SOUTH:
  case NORTH:
    return CUBE_F_B_VERTICES;
  case WEST:
  case EAST:
    return CUBE_L_R_VERTICES;
  }
}

const glm::ivec3 DIRECTIONS[] = {glm::ivec3(0, 1, 0),  glm::ivec3(0, 0, 1),
                                 glm::ivec3(-1, 0, 0), glm::ivec3(1, 0, 0),
                                 glm::ivec3(0, 0, -1), glm::ivec3(0, -1, 0)};

struct CubeFace {
  enum Direction direction;
  glm::vec3 position;

  /**
   * blockVertex
   * returns a std::vector<CubeVertex>, containing Position, Normal, and uv
   */
  std::vector<CubeVertex> blockVertex(glm::vec3 blockPosition,
                                      const std::vector<glm::vec2> uvs) const {
    auto vertices = getVerticesByFaceDirection(direction);
    std::vector<CubeVertex> vertexes;
    for (size_t i = 0; i < 4; i++) {
      vertexes.push_back({.Position = vertices[i] * position + blockPosition,
                          .Normal = DIRECTIONS[direction],
                          .uv = uvs[i]});
    }
    return vertexes;
  }

  /**
   * plainVertex
   * returns a std::vector<PlainVertex>, containing Position, Normal, and uv
   */
  std::vector<PlainTextureVertex> plainVertex(glm::vec3 blockPosition) const {
    auto vertices = getVerticesByFaceDirection(direction);
    std::vector<PlainTextureVertex> vertexes;
    for (size_t i = 0; i < 4; i++) {
      vertexes.push_back({.Position = vertices[i] * position + blockPosition});
    }
    return vertexes;
  }
};

static const std::vector<CubeFace> CUBE_FACES{
    {TOP, glm::vec3(1, 1, 1)},    {SOUTH, glm::vec3(1, 1, 1)},
    {EAST, glm::vec3(1, 1, 1)},   {WEST, glm::vec3(-1, 1, 1)},
    {NORTH, glm::vec3(1, 1, -1)}, {DOWN, glm::vec3(1, -1, 1)},
};

#endif
