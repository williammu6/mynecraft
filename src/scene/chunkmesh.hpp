#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include "../common.hpp"
#include "../gfx/gfx.hpp"
#include "../gfx/primitive.hpp"
#include "../state.hpp"
#include "blocks/block.hpp"

class ChunkMesh {
private:
  std::unique_ptr<Primitive> primitive;

public:
  ChunkMesh() {
    primitive = std::make_unique<Primitive>();
  };
  ~ChunkMesh() {
  }

  void draw(glm::vec3 position, struct Texture *texture);
  void add_face(CubeFace cube_face, glm::ivec3 position,
                glm::vec2 texture_offset, RenderType render_type,
                TextureRotation texture_rotations);
  void setup() {
    this->primitive->prepare();
  };
};

#endif
