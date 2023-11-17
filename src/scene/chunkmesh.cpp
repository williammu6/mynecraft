#include "chunkmesh.hpp"

void ChunkMesh::draw(glm::vec3 position, struct Texture *texture) {
  primitive->draw(position, state.renderer->shaders[Shaders::BLOCK], *texture);
}

constexpr std::array<int, 4> degrees_0_drawing_order = {0, 1, 2, 3};
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

void ChunkMesh::add_face(CubeFace cube_face, glm::ivec3 position,
                         glm::vec2 texture_offset, RenderType render_type,
                         TextureRotation rotation) {
  Texture texture = state.renderer->textures[TextureID::ATLAS];

  auto face_direction = DIRECTIONS[cube_face.direction];

  float minTX = texture.tile_size * texture_offset.x / texture.width;
  float maxTX = texture.tile_size * (texture_offset.x + 1) / texture.width;
  float minTY = texture.tile_size * texture_offset.y / texture.height;
  float maxTY = texture.tile_size * (texture_offset.y + 1) / texture.height;

  std::vector<glm::vec2> uvs = getRotatedTexCoordinates(
      {{minTX, minTY}, {maxTX, minTY}, {minTX, maxTY}, {maxTX, maxTY}},
      rotation);

  std::vector<CubeVertex> vertices = cube_face.blockVertex(position, uvs);

  primitive->push(vertices, QUAD_FACE_INDICES[cube_face.direction],
                  render_type);
}
