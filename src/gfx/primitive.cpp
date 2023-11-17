#include "primitive.hpp"
#include <memory>

/** VertexBuffer */
VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer() {
  // glDeleteBuffers(1, &id);
}
void VertexBuffer::bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, id);
}
void VertexBuffer::unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
};

/** IndexBuffer */
IndexBuffer::IndexBuffer(const void *data, unsigned int count)
    : m_count(count) {
  glGenBuffers(1, &id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int), data,
               GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
  glDeleteBuffers(1, &id);
}
void IndexBuffer::bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}
void IndexBuffer::unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};
