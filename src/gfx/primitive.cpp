#include "primitive.hpp"
#include <memory>

struct VertexAttrib {
  GLenum type;
  GLint size;
  GLboolean normalized;
};

std::vector<VertexAttrib> vertex_attribs{
    {GL_FLOAT, 3, GL_FALSE}, // Position
    {GL_FLOAT, 3, GL_FALSE}, // Normal
    {GL_FLOAT, 2, GL_FALSE}, // Texture
};

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
Primitive::Primitive() {
  glGenVertexArrays(1, &VAO);
};
Primitive::~Primitive() {
  glDeleteVertexArrays(1, &VAO);
  indices_map.clear();
  ib_map.clear();
  vertices.clear();
  vertices.shrink_to_fit();
}

void Primitive::prepare() {
  vb = std::make_unique<VertexBuffer>(static_cast<void *>(vertices.data()),
                                      4 * vertices.size() * sizeof(Vertex));

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

void Primitive::draw(const glm::vec3 &position, Shader *shader,
                     const Texture &texture) {
  shader->use();
  shader->setUniforms(position);
  glActiveTexture(GL_TEXTURE + (int)texture.id);
  glBindTexture(GL_TEXTURE_2D, texture.pixels);

  glBindVertexArray(VAO);
  vb->bind();

  for (const auto type : {RenderType::NORMAL, RenderType::TRANSPARENT}) {
    ib_map[type]->bind();

    shader->setUniform("material.opacity",
                       type == RenderType::TRANSPARENT ? 0.6f : 1.0f);

    glDrawElements(GL_TRIANGLES, indices_map[type].size(), GL_UNSIGNED_INT,
                   (void *)0);
  }
}

void Primitive::push(const std::vector<Vertex> &v,
                     std::vector<unsigned int> _indices,
                     RenderType render_type) {
  vertices.insert(vertices.end(), v.begin(), v.end());
  for (auto i : _indices)
    indices_map[render_type].push_back(i + n_faces * 4);
  n_faces++;
}
