#ifndef VERTEX_H
#define VERTEX_H

#include "../gfx.hpp"
#include "vertex_buffer.hpp"

struct VertexAttrib {
  GLenum type;
  GLint size;
  GLboolean normalized;
};

constexpr VertexAttrib positionAttrib = {
    .type = GL_FLOAT,
    .size = 3,
    .normalized = GL_FALSE,
};

constexpr VertexAttrib normalAttrib = {
    .type = GL_INT,
    .size = 3,
    .normalized = GL_FALSE,
};

constexpr VertexAttrib uvAttrib = {
    .type = GL_FLOAT,
    .size = 2,
    .normalized = GL_FALSE,
};

struct CubeVertex {
  glm::vec3 position;
  glm::ivec3 normal;
  glm::vec2 uv;
};

struct PlainTextureVertex {
  glm::vec3 position;
  glm::vec2 uv;
};

#endif
