#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "../gfx.hpp"

class VertexBuffer {
private:
  unsigned int id;

public:
  VertexBuffer(const void *data, unsigned int size) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  };
  ~VertexBuffer() {
    glDeleteBuffers(1, &id);
  };

  void bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id);
  };
  void unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  };
};

#endif
