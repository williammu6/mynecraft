#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include "../common.hpp"
#include "../gfx/gfx.hpp"
#include "../gfx/primitive.hpp"
#include "../state.hpp"

class ChunkMesh {
public:
  ChunkMesh() {
    this->primitive = new Primitive();
    this->indices = {};
    this->vertices = {};
  };
  ~ChunkMesh() { clean(); }

  struct Primitive *primitive;

  void draw(glm::vec3 position, struct Texture *texture);
  void add_face(CubeFace cube_face, glm::vec3 position,
                glm::vec2 texture_offset);
  void setup();
  void clean() {
    this->vertices.clear();
    this->vertices.shrink_to_fit();
    this->indices.clear();
    this->indices.shrink_to_fit();
  }

private:
  unsigned int VAO, VBO, EBO;

  std::vector<std::vector<Vertex>> vertices;
  std::vector<std::vector<unsigned int>> indices;
};

#endif
