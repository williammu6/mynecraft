#include "primitive.hpp"

/** VertexBuffer */
VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &id);
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

/** Primitive */
/** Primitive */
Primitive::Primitive(){};
Primitive::~Primitive() {
  glDeleteVertexArrays(1, &VAO);
  delete ib;
  delete vb;
}

void Primitive::clean() {
  indices.clear();
  indices.shrink_to_fit();
  vertices.clear();
  vertices.shrink_to_fit();
}

void Primitive::prepare() {
  vb = new VertexBuffer(static_cast<void *>(vertices.data()),
                        4 * vertices.size() * sizeof(Vertex));
  ib = new IndexBuffer(static_cast<void *>(indices.data()), indices.size());

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  vb->bind();
  ib->bind();

  for (unsigned int locIndex = 0; locIndex <= 2; locIndex++) {
    glVertexAttribPointer(locIndex, vertexSizes[locIndex], GL_FLOAT, GL_FALSE,
                          8 * sizeof(float),
                          (void *)(3 * locIndex * sizeof(float)));
    glEnableVertexAttribArray(locIndex);
  }
}

void Primitive::draw(const glm::vec3 &position, Shader *shader,
                     const Texture &texture) {
  shader->use();
  shader->setUniforms(position);

  glBindVertexArray(VAO);
  vb->bind();
  ib->bind();

  glActiveTexture(GL_TEXTURE + (int)texture.id);
  glBindTexture(GL_TEXTURE_2D, texture.pixels);

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void *)0);

  ib->unbind();
  vb->unbind();
}

void Primitive::push(const std::vector<Vertex> &v,
                     std::vector<unsigned int> _indices) {
  vertices.insert(vertices.end(), v.begin(), v.end());
  for (auto i : _indices)
    indices.push_back(i + n_faces * 4);
  n_faces++;
}
