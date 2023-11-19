#include "mesh.hpp"

using VertexLayout = std::vector<VertexAttrib>;

/*
template <> void Mesh<PlainTextureVertex>::prepare() {
  vb = std::make_unique<VertexBuffer>(static_cast<void *>(vertices.data()),
                                      4 * vertices.size() *
                                          sizeof(PlainTextureVertex));

  glBindVertexArray(VAO);
  vb->bind();

  for (const auto type : {RenderType::NORMAL, RenderType::TRANSPARENT}) {
    ib_map[type] = std::make_unique<IndexBuffer>(
        static_cast<void *>(indices_map[type].data()),
        indices_map[type].size());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PlainTextureVertex),
                          (void *)offsetof(PlainTextureVertex, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(PlainTextureVertex),
                          (void *)offsetof(PlainTextureVertex, uv));
    glEnableVertexAttribArray(1);
  }
}
*/
