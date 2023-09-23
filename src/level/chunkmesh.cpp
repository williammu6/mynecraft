#include "chunkmesh.hpp"

void ChunkMesh::draw(glm::vec3 position, struct Texture *texture) {
  primitive->draw(position, state.renderer->block_shader, *texture);
}

void ChunkMesh::add_face(CubeFace cube_face, glm::ivec3 position,
                         glm::vec2 texture_offset, RenderType render_type) {
  Texture texture = state.renderer->textures[TextureID::ATLAS];

  auto face_direction = DIRECTIONS[cube_face.direction];
  face_direction.y *= -1;

  float minTX = texture.tile_size * texture_offset.x / texture.width;
  float maxTX = texture.tile_size * (texture_offset.x + 1) / texture.width;
  float minTY = texture.tile_size * texture_offset.y / texture.height;
  float maxTY = texture.tile_size * (texture_offset.y + 1) / texture.height;

  std::vector<glm::vec3> V = cube_face.vertices();
  glm::vec3 f_pos = position;

  std::vector<Vertex> v{{{V[0] * cube_face.position + f_pos, face_direction,
                          glm::vec2(minTX, minTY)},
                         {V[1] * cube_face.position + f_pos, face_direction,
                          glm::vec2(maxTX, minTY)},
                         {V[2] * cube_face.position + f_pos, face_direction,
                          glm::vec2(minTX, maxTY)},
                         {V[3] * cube_face.position + f_pos, face_direction,
                          glm::vec2(maxTX, maxTY)}}};

  primitive->push(v, QUAD_FACE_INDICES[cube_face.direction], render_type);
}
