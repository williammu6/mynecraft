#include "chunkmesh.hpp"
#include "../gfx/Mesh/mesh.hpp"
#include "../state.hpp"
#include <array>

constexpr std::array<int, 4> degrees_0_drawing_order{0, 1, 2, 3};
constexpr std::array<int, 4> degrees_90_drawing_order{1, 3, 0, 2};
constexpr std::array<int, 4> degrees_180_drawing_order{3, 1, 2, 0};
constexpr std::array<int, 4> degrees_270_drawing_order{2, 0, 3, 1};

std::vector<glm::vec2>
getRotatedTexCoordinates(const std::vector<glm::vec2> texCoords,
                         TextureRotation rotation) {
  std::vector<glm::vec2> rotatedTexCoordinates;
  switch (rotation) {
  case TextureRotation::DEGREES_90:
    for (const int i : degrees_90_drawing_order)
      rotatedTexCoordinates.push_back(texCoords[i]);
    break;
  case TextureRotation::DEGREES_180:
    for (const int i : degrees_180_drawing_order)
      rotatedTexCoordinates.push_back(texCoords[i]);
    break;
  case TextureRotation::DEGREES_270:
    for (const int i : degrees_270_drawing_order)
      rotatedTexCoordinates.push_back(texCoords[i]);
    break;
  default:
    return texCoords;
  }
  return rotatedTexCoordinates;
}

void ChunkMesh::addBlockFace(CubeFace cubeFace, glm::ivec3 position,
                             glm::vec2 textureOffset, RenderType renderType,
                             float localLight, TextureRotation rotation) {
  Texture texture = state.renderer->textures[TextureID::ATLAS];

  float minTX = texture.tileSize * textureOffset.x / texture.width;
  float maxTX = texture.tileSize * (textureOffset.x + 1) / texture.width;
  float minTY = texture.tileSize * textureOffset.y / texture.height;
  float maxTY = texture.tileSize * (textureOffset.y + 1) / texture.height;

  std::vector<glm::vec2> uvs = getRotatedTexCoordinates(
      {{minTX, minTY}, {maxTX, minTY}, {minTX, maxTY}, {maxTX, maxTY}},
      rotation);

  std::vector<CubeVertex> vertices =
      cubeFace.blockVertex(position, uvs, localLight);

  mesh->push(vertices, QUAD_FACE_INDICES[cubeFace.direction], renderType);
}

void ChunkMesh::draw(glm::vec3 position, Texture *texture) {
  mesh->drawType(position, state.renderer->shaders[Shaders::BLOCK], *texture,
                 RenderType::NORMAL);

  mesh->drawType(position, state.renderer->shaders[Shaders::BLOCK], *texture,
                 RenderType::TRANSPARENT);
}

void ChunkMesh::setup() {
  mesh->addVertexBuffer(
      {positionAttrib, normalAttrib, uvAttrib, positionAttrib});
}
