#ifndef MESH_H
#define MESH_H

#include "../../common.hpp"
#include "../gfx.hpp"
#include "../shader.hpp"
#include "../texture.hpp"
#include "index_buffer.hpp"
#include "vertex.hpp"
#include "vertex_buffer.hpp"

enum class RenderType { NORMAL = 0, TRANSPARENT };

const std::vector<RenderType> renderTypes{RenderType::NORMAL,
                                          RenderType::TRANSPARENT};

inline std::vector<VertexAttrib> vertex_attribs{
    {GL_FLOAT, 3, GL_FALSE}, // Position
    {GL_FLOAT, 3, GL_FALSE}, // Normal
    {GL_FLOAT, 2, GL_FALSE}, // Texture
};

/**
 * @tparam type of the Vertex
 */
template <typename T> class Mesh {
private:
  unsigned int VAO;
  std::unique_ptr<VertexBuffer> vb;

  std::vector<T> vertices;
  std::map<RenderType, std::vector<unsigned int>> indices_map;
  std::map<RenderType, std::unique_ptr<IndexBuffer>> ib_map;
  int n_faces = 0;

public:
  Mesh() {
    glGenVertexArrays(1, &VAO);
  }
  // Mesh(const std::vector<T> vertices);
  // Mesh(const std::vector<T> vertices, const std::vector<unsigned int>
  // indices);
  Mesh(const std::vector<T> vertices, const std::vector<unsigned int> indices,
       RenderType renderType) {
    glGenVertexArrays(1, &VAO);
    push(vertices, indices, renderType);
  };

  ~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    indices_map.clear();
    ib_map.clear();
    vertices.clear();
    vertices.shrink_to_fit();
  }

  void addVertexBuffer(const std::vector<VertexAttrib> &attributes) {
    glBindVertexArray(VAO);
    createBuffers();
    vb->bind();

    unsigned long attributeOffset = 0;
    unsigned int attributeIndex = 0;

    for (const auto &attribute : attributes) {
      glVertexAttribPointer(attributeIndex, attribute.size, attribute.type,
                            attribute.normalized, sizeof(T),
                            (void *)(attributeOffset));
      glEnableVertexAttribArray(attributeIndex);
      attributeIndex++;
      attributeOffset += attribute.size * sizeof(attribute.type);
    }
  };

  void createBuffers() {
    for (const auto &renderType : renderTypes) {
      if (indices_map[renderType].empty()) {
        continue;
      }
      ib_map[renderType] =
          std::make_unique<IndexBuffer>((void *)indices_map[renderType].data(),
                                        indices_map[renderType].size());
    }

    vb = std::make_unique<VertexBuffer>((void *)vertices.data(),
                                        4 * vertices.size() * sizeof(T));
  }

  void draw(const glm::vec3 &position, Shader *shader, const Texture &texture) {
    shader->use();
    shader->setUniforms(position);
    glActiveTexture(GL_TEXTURE + static_cast<int>(texture.id));
    glBindTexture(GL_TEXTURE_2D, texture.pixels);

    glBindVertexArray(VAO);
    vb->bind();

    for (const auto &renderType : renderTypes) {
      if (indices_map[renderType].size() == 0)
        continue;
      ib_map[renderType]->bind();
      // TODO: do this some other way
      // TODO: this is only here because blocks and water share the same VAO and VBO
      shader->setUniform("material.opacity", renderType == RenderType::TRANSPARENT ? 0.6f : 1.0f);
      glDrawElements(GL_TRIANGLES, indices_map[renderType].size(),
                     GL_UNSIGNED_INT, (void *)0);
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
            RenderType renderType) {
    vertices.insert(vertices.end(), v.begin(), v.end());
    for (auto i : _indices)
      indices_map[renderType].push_back(i + n_faces * 4);
    n_faces++;
  };

  void reset() {
    vertices.erase(vertices.begin(), vertices.end());
    vertices.shrink_to_fit();
  }
};

#endif
