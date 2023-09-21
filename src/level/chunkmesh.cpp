#include "chunkmesh.hpp"

void ChunkMesh::setup() {
  std::vector<Vertex> all_vertices;
  std::vector<unsigned int> all_indices;

  for (auto vertex : vertices)
    all_vertices.insert(all_vertices.end(), vertex.begin(), vertex.end());

  for (int index = 0; index < indices.size(); index++) {
    for (auto in : indices[index]) {
      all_indices.push_back(in + index * 4);
    }
  }

  primitive->prepare(all_vertices, all_indices);
}

void ChunkMesh::draw(glm::vec3 position, struct Texture *texture) {
  primitive->draw(position, state.renderer->block_shader, *texture);
}

void ChunkMesh::add_face(CubeFace cube_face, glm::ivec3 position,
                         glm::vec2 texture_offset) {
  Texture texture = state.renderer->textures[TextureID::ATLAS];

  auto face_direction = DIRECTIONS[cube_face.direction];

  float minTX = texture.tile_size * texture_offset.x / texture.width;
  float maxTX = texture.tile_size * (texture_offset.x + 1) / texture.width;
  float minTY = texture.tile_size * texture_offset.y / texture.height;
  float maxTY = texture.tile_size * (texture_offset.y + 1) / texture.height;

  std::vector<glm::vec3> V = cube_face.vertices();
  glm::vec3 f_pos = position;

  this->vertices.push_back(
      {{V[0] * cube_face.position + f_pos, face_direction, glm::vec2(minTX, minTY)},
       {V[1] * cube_face.position + f_pos, face_direction, glm::vec2(maxTX, minTY)},
       {V[2] * cube_face.position + f_pos, face_direction, glm::vec2(minTX, maxTY)},
       {V[3] * cube_face.position + f_pos, face_direction, glm::vec2(maxTX, maxTY)}});

  this->indices.push_back(QUAD_FACE_INDICES[cube_face.direction]);
}
