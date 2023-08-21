#include "chunk.hpp"
#include "world.hpp"
#include <cstdio>
#include <iostream>

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

Chunk *Chunk::get_neighbor_chunk(Direction direction) {
  /*
  if (direction == NORTH)
    return this->world->get_chunk_at(this->position.x, this->position.z - 1);
  if (direction == WEST)
    return this->world->get_chunk_at(this->position.x - 1, this->position.z);
  if (direction == EAST)
    return this->world->get_chunk_at(this->position.x + 1, this->position.z);
    */

  if (direction == SOUTH)
    return this->world->get_chunk_at(this->position.x + 1, this->position.z);

  return nullptr;
}

Block *Chunk::get_neighbor_block(Direction direction, Block *block) {
  int x = block->position.x;
  int y = block->position.y;
  int z = block->position.z;

  if (direction == SOUTH) {
    if (z != SIZE - 1) {
      return this->get_block(x, y, z + 1);
    }
    Chunk *neighbor_chunk =
        this->world->get_chunk_at(this->position.x, this->position.z + 1);
    if (neighbor_chunk == nullptr)
      return nullptr;
    Block *neighbor_block = neighbor_chunk->get_block(x, y, 0);
    return neighbor_chunk->get_block(x, y, 0);
  }

  if (direction == NORTH) {
    if (z != 0) {
      return this->get_block(x, y, z - 1);
    }
    Chunk *neighbor_chunk =
        this->world->get_chunk_at(this->position.x, this->position.z - 1);
    if (neighbor_chunk == nullptr)
      return nullptr;
    return neighbor_chunk->get_block(x, y, SIZE - 1);
  }

  if (direction == WEST) {
    if (x != 0) {
      return this->get_block(x - 1, y, z);
    }
    Chunk *neighbor_chunk =
        this->world->get_chunk_at(this->position.x - 1, this->position.z);
    if (neighbor_chunk == nullptr)
      return nullptr;
    return neighbor_chunk->get_block(SIZE - 1, y, z);
  }

  if (direction == EAST) {
    if (x != SIZE - 1) {
      return this->get_block(x + 1, y, z);
    }
    Chunk *neighbor_chunk =
        this->world->get_chunk_at(this->position.x + 1, this->position.z);
    if (neighbor_chunk == nullptr)
      return nullptr;
    return neighbor_chunk->get_block(0, y, z);
  }

  return nullptr;
}

bool should_draw_block_face(Chunk *chunk, Direction direction,
                            glm::vec3 position) {
  Block *block = chunk->get_block(position.x, position.y, position.z);
  Block *neigh_block = chunk->get_neighbor_block(direction, block);
  return neigh_block == nullptr || !neigh_block->type->solid;
}

void Chunk::prepare_render() {
  for (int x = 0; x < this->SIZE; x++) {
    for (int z = 0; z < this->SIZE; z++) {
      int height = this->blocks[x][z].size();
      for (int y = height - 1; y >= 0; y--) {
        Block block = this->blocks[x][z][y];

        if (!should_draw_block(x, y, z)) {
          continue;
        }

        if (should_draw_block_face(this, SOUTH, {x, y, z}))
          this->add_face_to_mesh(CUBE_FACES[SOUTH], block);

        if (should_draw_block_face(this, NORTH, {x, y, z}))
          this->add_face_to_mesh(CUBE_FACES[NORTH], block);

        if (should_draw_block_face(this, WEST, {x, y, z}))
          this->add_face_to_mesh(CUBE_FACES[WEST], block);

        if (should_draw_block_face(this, EAST, {x, y, z}))
          this->add_face_to_mesh(CUBE_FACES[EAST], block);

        for (const auto &cube_face : CUBE_FACES) {
          if (cube_face.face == TOP)
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
  return x > 0 && y >= 0 && z >= 0 && x < this->SIZE && z < this->SIZE &&
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
      // height = z + 1;

      if (this->position.z == 0)
        block_type = new Grass();
      if (this->position.z == 1)
        block_type = new Cobblestone();

      for (int y = 0; y < height; y++) {
        blocks[x][z].push_back({block_type, glm::vec3(x, y, z)});
      }

      for (int y = height; y < 64; y++) {
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

  // this->prepare_render();
}

Chunk *create_chunk(glm::vec3 position, struct World *world) {
  Chunk *chunk = new Chunk(position, world);
  chunk->generate();
  return chunk;
}
