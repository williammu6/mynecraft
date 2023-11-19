#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include "../common.hpp"
#include "../gfx/Mesh/mesh.hpp"
#include "../gfx/cube_face.hpp"
#include "../gfx/gfx.hpp"
#include "../state.hpp"
#include "blocks/block.hpp"

class ChunkMesh {
  using VertexType = CubeVertex;

private:
  std::unique_ptr<Mesh<VertexType>> mesh;

public:
  ChunkMesh() {
    mesh = std::make_unique<Mesh<VertexType>>();
  };
  ~ChunkMesh() {
  }

  void add_face(CubeFace cube_face, glm::ivec3 position,
                glm::vec2 texture_offset, RenderType render_type,
                TextureRotation texture_rotations);

  void draw(glm::vec3 position, struct Texture *texture) {
    mesh->draw(position, state.renderer->shaders[Shaders::BLOCK], *texture);
  }

  void setup() {
    mesh->addVertexBuffer({positionAttrib, normalAttrib, uvAttrib});
  }
};

#endif
