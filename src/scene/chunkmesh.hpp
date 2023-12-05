#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include "../gfx/Mesh/mesh.hpp"
#include "../gfx/cube_face.hpp"
#include "../gfx/texture.hpp"
#include "blocks/block.hpp"

class ChunkMesh {
  using VertexType = CubeVertex;

private:
  std::unique_ptr<Mesh<VertexType>> mesh;

public:
  ChunkMesh() {
    mesh = std::make_unique<Mesh<VertexType>>();
  };

  void addBlockFace(CubeFace cubeFace, glm::ivec3 position,
                    glm::vec2 textureOffset, RenderType renderType,
                    TextureRotation textureRotations);
  void draw(glm::vec3 position, Texture *texture);
  void setup();
};

#endif
