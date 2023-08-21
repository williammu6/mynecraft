#include "chunk.hpp"
#include "world.hpp"
#include <cstdio>

void Chunk::add_face_to_mesh(CubeFace cf, Block &block) {
  TextureAtlas *texture_atlas = state.renderer->texture_atlas;
  auto texture_offset = block.type->texture_offset(cf.face);

  auto face_direction = DIRECTIONS[cf.ID];

  int nx = block.position.x + face_direction.x;
  int ny = block.position.y + face_direction.y;
  int nz = block.position.z + face_direction.z;

  if (nx >= 0 && ny >= 0 && nz >= 0 && nx < this->SIZE &&
      ny < this->blocks[nx][nz].size() && nz < this->SIZE &&
      this->blocks[nx][nz][ny].type->solid) {
    return;
  }

  float minTX =
      texture_atlas->tW * texture_offset.x / texture_atlas->atlas_width;

  float maxTX =
      texture_atlas->tW * (texture_offset.x + 1) / texture_atlas->atlas_width;

  float minTY =
      texture_atlas->tH * texture_offset.y / texture_atlas->atlas_height;

  float maxTY =
      texture_atlas->tH * (texture_offset.y + 1) / texture_atlas->atlas_height;

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

void Chunk::prepare_block(Block &block) {}

void Chunk::render() { this->mesh->draw(this->position * (float)this->SIZE); }

void Chunk::init() {
  this->blocks.resize(this->SIZE);
  for (int i = 0; i < this->SIZE; i++)
    this->blocks[i].resize(this->SIZE);
}

void Chunk::prepare_render() {
  std::map<Face, Chunk *> neighbor_chunks{
      {LEFT, this->world->get_chunk_at(position.x + 1, position.z)},
      {RIGHT, this->world->get_chunk_at(position.x - 1, position.z)},
      {FRONT, this->world->get_chunk_at(position.x, position.z + 1)},
      {BACK, this->world->get_chunk_at(position.x, position.z - 1)}};

  for (int x = 0; x < this->SIZE; x++) {
    for (int z = 0; z < this->SIZE; z++) {
      int height = this->blocks[x][z].size();
      for (int y = height - 1; y >= 0; y--) {
        Block block = this->blocks[x][z][y];

        if (!should_draw_block(x, y, z)) {
          continue;
        }

        if (block.type->name == "cactus") {
          printf("LULULUL %f %f\n", block.position.x, block.position.z);
        }

        Block *neighbor_block_left =
            x == SIZE - 1 ? neighbor_chunks[LEFT] != nullptr
                                ? neighbor_chunks[LEFT]->get_block(0, y, z)
                                : NULL
                          : this->get_block(x + 1, y, z);

        if (neighbor_block_left == NULL ||
            neighbor_block_left != nullptr &&
                !neighbor_block_left->type->solid) {
          this->add_face_to_mesh(CUBE_FACES[LEFT], block);
        }

        Block *neighbor_block_right =
            x == 0 ? neighbor_chunks[RIGHT] != nullptr
                         ? neighbor_chunks[RIGHT]->get_block(SIZE - 1, y, z)
                         : NULL
                   : this->get_block(x - 1, y, z);

        if (neighbor_block_right == NULL ||
            neighbor_block_right != nullptr &&
                !neighbor_block_right->type->solid) {
          this->add_face_to_mesh(CUBE_FACES[3], block);
        }

        for (const auto &cube_face : CUBE_FACES) {
          if (cube_face.face == LEFT)
            continue;
          if (cube_face.face == RIGHT)
            continue;

          this->add_face_to_mesh(cube_face, block);
        }
      }
    }
  }

  this->mesh = new Mesh(this->vertices, this->indices);
}

Block *Chunk::get_block(int x, int y, int z) {
  if (in_bounds({x, y, z})) {
    return &this->blocks[x][z][y];
  }

  return nullptr;
}

bool Chunk::should_draw_block(int x, int y, int z) {
  Block *block = get_block(x, y, z);

  return block->type->solid;
}

bool Chunk::in_bounds(glm::vec3 position) {
  float x = this->position.x;
  float y = this->position.y;
  float z = this->position.z;
  return x >= 0 && y >= 0 && z >= 0 && x < this->SIZE && z < this->SIZE &&
         y < this->blocks[x][z].size();
}

void Chunk::set(glm::vec3 position, Block block) {
  if (in_bounds(position))
    blocks[position.x][position.z][position.y] = block;
}

void Chunk::generate() {
  BlockType *block_type = nullptr;

  const siv::PerlinNoise::seed_type seed = 2u;
  const siv::PerlinNoise perlin{seed};

  for (int x = 0; x < this->SIZE; x++) {
    int nX = (x + 1) + position.x * this->SIZE;
    for (int z = 0; z < this->SIZE; z++) {
      int nZ = (z + 1) + position.z * this->SIZE;
      const double noise = perlin.octave2D_01(nX * 0.01, nZ * 0.01, 4);
      int height = glm::max(1, (int)(noise * 64));

      if (height < 10) {
        block_type = new Water();
      } else if (height < 14) {
        block_type = new Sand();
      } else if (height < 96) {
        block_type = new Grass();
      } else {
        block_type = new Snow();
      }

      height = x + 10;

      for (int y = 0; y < height; y++) {
        blocks[x][z].push_back({block_type, glm::vec3(x, y, z)});
      }

      for (int y = height; y < 256; y++) {
        blocks[x][z].push_back({new Air(), glm::vec3(x, y, z)});
      }

      if (RANDCHANCE(0.02) && strcmp(block_type->name, "sand") == 0) {
        for (int cY = height; cY < height + RAND(3, 5); cY++) {
          glm::vec3 cactus_position = {x, cY, z};
          this->set(cactus_position, {new Cactus(), cactus_position});
        }
      }

      if (RANDCHANCE(0.01) && strcmp(block_type->name, "grass") == 0) {
        // create_tree({x, height, z}, this);
      }
    }
  }

  this->prepare_render();
}

Chunk *create_chunk(glm::vec3 position, struct World *world) {
  Chunk *chunk = new Chunk(position, world);
  chunk->generate();
  return chunk;
}
