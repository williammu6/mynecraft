#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "../gfx.hpp"

class IndexBuffer {
private:
  unsigned int id;
  unsigned int m_count;

public:
  IndexBuffer(const void *data, unsigned int count) : m_count(count) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int), data,
                 GL_STATIC_DRAW);
  };
  ~IndexBuffer() {
    glDeleteBuffers(1, &id);
  };

  void bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
  };

  void unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  };

  unsigned int get_count() const {
    return m_count;
  }
};

#endif
