#include "primitive.hpp"
#include <memory>
#include <type_traits>

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

template <> void Primitive<CubeVertex>::prepare() {
  vb = std::make_unique<VertexBuffer>(static_cast<void *>(vertices.data()),
                                      4 * vertices.size() * sizeof(CubeVertex));

  glBindVertexArray(VAO);
  vb->bind();

  for (const auto type : {RenderType::NORMAL, RenderType::TRANSPARENT}) {
    ib_map[type] = std::make_unique<IndexBuffer>(
        static_cast<void *>(indices_map[type].data()),
        indices_map[type].size());

    for (int vertex_idx = 0; vertex_idx < vertex_attribs.size(); vertex_idx++) {
      VertexAttrib vertex_attrib = vertex_attribs[vertex_idx];
      glVertexAttribPointer(vertex_idx, vertex_attrib.size, vertex_attrib.type,
                            vertex_attrib.normalized, 8 * sizeof(float),
                            (void *)(vertex_idx * 3 * sizeof(float)));
      glEnableVertexAttribArray(vertex_idx);
    }
  }
}

template <> void Primitive<PlainTextureVertex>::prepare() {
  vb = std::make_unique<VertexBuffer>(static_cast<void *>(vertices.data()),
                                      4 * vertices.size() *
                                          sizeof(PlainTextureVertex));

  glBindVertexArray(VAO);
  vb->bind();

  for (const auto type : {RenderType::NORMAL, RenderType::TRANSPARENT}) {
    ib_map[type] = std::make_unique<IndexBuffer>(
        static_cast<void *>(indices_map[type].data()),
        indices_map[type].size());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PlainTextureVertex), (void *)offsetof(PlainTextureVertex, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(PlainTextureVertex), (void *)offsetof(PlainTextureVertex, uv));
    glEnableVertexAttribArray(1);
  }
}

/*
template <typename T>
void Primitive<T>::addVertexBuffer(
    const std::vector<VertexAttrib> &attributes) {
  vb = std::make_unique<VertexBuffer>(static_cast<void *>(vertices.data()),
                                      4 * vertices.size() * sizeof(T));
  glBindVertexArray(VAO);
  vb->bind();

  for (const auto &attrib : attributes) {
    glVertexAttribPointer(attrib.index, attrib.size, attrib.type,
                          attrib.normalized, attrib.stride, attrib.offset);
    glEnableVertexAttribArray(attrib.index);
  }
}
*/
