#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include "../common.hpp"
#include "../gfx/gfx.hpp"
#include "../gfx/primitive.hpp"
#include "../state.hpp"

struct Block;

class ChunkMesh {
private:
  Primitive *primitive;

public:
  ChunkMesh() {
    this->primitive = new Primitive();
  };
  ~ChunkMesh() {
    delete this->primitive;
  }

  void draw(glm::vec3 position, struct Texture *texture);
  void add_face(CubeFace cube_face, glm::ivec3 position,
                glm::vec2 texture_offset, RenderType render_type);
  void setup() {
    this->primitive->prepare();
  };
};

#endif
