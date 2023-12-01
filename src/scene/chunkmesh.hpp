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

  void addBlockFace(CubeFace cubeFace, glm::ivec3 position,
                    glm::vec2 textureOffset, RenderType renderType,
                    TextureRotation textureRotations);

  void draw(glm::vec3 position, struct Texture *texture) {
    mesh->draw(position, state.renderer->shaders[Shaders::BLOCK], *texture);
  }

  void setup() {
    mesh->addVertexBuffer(
        {positionAttrib, normalAttrib, uvAttrib, positionAttrib});
  }
};

#endif
