#include "chunk.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <utility>

void Chunk::add_face_to_mesh(CubeFace cf, Block &block) {
  auto texture_offset = block.type->texture_offset(cf.face);

  auto face_direction = DIRECTIONS[cf.ID];

  int nx = block.position.x + face_direction.x;
  int ny = block.position.y + face_direction.y;
  int nz = block.position.z + face_direction.z;

  if (nx >= 0 && ny >= 0 && nz >= 0 && nx < this->size && ny < this->blocks[nx][nz].size() &&
      nz < this->size && this->blocks[nx][nz][ny].type->solid) {
    return;
  }

  float minTX =
      this->texture_atlas->tW * texture_offset.x / this->texture_atlas->atlasW;

  float maxTX = this->texture_atlas->tW * (texture_offset.x + 1) /
                this->texture_atlas->atlasW;

  float minTY =
      this->texture_atlas->tH * texture_offset.y / this->texture_atlas->atlasH;

  float maxTY = this->texture_atlas->tH * (texture_offset.y + 1) /
                this->texture_atlas->atlasH;

  glm::vec3 *V = cf.vertices();

  std::vector<Vertex> tmpVertices{{V[0] * cf.position + block.position,
                                   face_direction, glm::vec2(minTX, minTY)},
                                  {V[1] * cf.position + block.position,
                                   face_direction, glm::vec2(maxTX, minTY)},
                                  {V[2] * cf.position + block.position,
                                   face_direction, glm::vec2(minTX, maxTY)},
                                  {V[3] * cf.position + block.position,
                                   face_direction, glm::vec2(maxTX, maxTY)}};

  this->vertices.push_back(tmpVertices);

  this->indices.push_back(QUAD_FACE_INDICES[cf.ID]);
}

void Chunk::prepare_block(Block &block) {
  for (const auto &cube_face : CUBE_FACES) {
    this->add_face_to_mesh(cube_face, block);
  }
}

void Chunk::render() {
  this->mesh->draw(this->shader, this->position * (float)this->size);
}

void Chunk::init() {
  this->blocks.resize(this->size);
  for (int i = 0; i < this->size; i++)
    this->blocks[i].resize(this->size);
}

void Chunk::prepare_render() {
  for (int x = 0; x < this->size; x++) {
    for (int z = 0; z < this->size; z++) {
      int height = this->blocks[x][z].size();
      for (int y = height - 1; y >= 0; y--) {
        Block block = this->blocks[x][z][y];

        if (!should_draw_block(x, y, z)) {
          continue;
        }

        this->prepare_block(this->blocks[x][z][y]);
      }
    }
  }

  this->mesh = new Mesh(this->vertices, this->indices);
}

Block* Chunk::get_block(int x, int y, int z) {
  if (x >= 0 && y >= 0 && z >= 0 && x < this->size && z < this->size && y < this->blocks[x][z].size()) {
    return &this->blocks[x][z][y];
  }

  return nullptr;
}

bool Chunk::should_draw_block(int x, int y, int z) {
  Block* block = get_block(x, y, z);
  return block->type->solid;
  bool render = false;
  const std::vector<std::vector<int>> coordinate_directions = {
    {-1, 0 },
    { 1, 0 },
    { 0, -1 },
    { 0, 1 },
  };
  
  Block* block_above = get_block(x, y + 1, z);
  if (block_above == nullptr) return true;

  for (auto dir : coordinate_directions) {
    int newX = x + dir[0];
    int newZ = z + dir[1];

    Block* neighbor_block = get_block(newX, y, newZ);

    if (neighbor_block == nullptr) {
      render = true;
    }
  }

  return render;
}
