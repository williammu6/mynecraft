#include "chunk.hpp"
#include "gen.hpp"
#include "world.hpp"

std::vector<Direction> directions{SOUTH, EAST, WEST, NORTH};

std::map<Direction, glm::vec3> direction_offset{{SOUTH, {0, 0, 1}},
                                                {NORTH, {0, 0, -1}},
                                                {WEST, {-1, 0, 0}},
                                                {EAST, {1, 0, 0}}};

void Chunk::add_face_to_mesh(CubeFace cf, Block block) {
  TextureAtlas *texture_atlas = state.renderer->texture_atlas;
  auto texture_offset = block.type->texture_offset(cf.direction);

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

void Chunk::render() {
  this->mesh->draw((glm::vec3)this->position * (float)this->SIZE);
}

void Chunk::init() {
  this->blocks.resize(this->SIZE);
  for (int i = 0; i < this->SIZE; i++)
    this->blocks[i].resize(this->SIZE);
}

Block *Chunk::get_neighbor_block(Direction direction, Block block) {
  int x = block.position.x;
  int y = block.position.y;
  int z = block.position.z;

  if (direction == SOUTH) {
    if (z != SIZE - 1) {
      return get_block(x, y, z + 1);
    } else if (neighbor_chunk[SOUTH]) {
      return &neighbor_chunk[SOUTH]->blocks[x][0][y];
    }
  }

  if (direction == NORTH) {
    if (z != 0) {
      return get_block(x, y, z - 1);
    } else if (neighbor_chunk[NORTH]) {
      return &neighbor_chunk[NORTH]->blocks[x][SIZE - 1][y];
    }
  }

  if (direction == WEST) {
    if (x != 0) {
      return this->get_block(x - 1, y, z);
    } else if (neighbor_chunk[WEST]) {
      return &neighbor_chunk[WEST]->blocks[SIZE - 1][z][y];
    }
  }

  if (direction == EAST) {
    if (x != SIZE - 1) {
      return get_block(x + 1, y, z);
    } else if (neighbor_chunk[EAST]) {
      return &neighbor_chunk[EAST]->blocks[0][z][y];
    }
  }
  return nullptr;
}

bool should_draw_block_face(Chunk *chunk, Direction direction,
                            glm::vec3 position) {
  Block *block = chunk->get_block(position.x, position.y, position.z);
  Block *neigh_block = chunk->get_neighbor_block(direction, *block);
  return neigh_block == nullptr || !neigh_block->type->solid;
}

void Chunk::prepare_render_borders() {
  this->indices = {};
  this->vertices = {};

  for (int x = 0; x < this->SIZE; x++) {
    for (int z = 0; z < this->SIZE; z++) {
      if (x == 0 || z == 0 || x == SIZE - 1 || z == SIZE - 1) {
        int height = this->blocks[x][z].size();
        for (int y = 0; y < height; y++) {
          Block block = this->blocks[x][z][y];
          if (!block.type->solid)
            continue;

          for (const auto &cube_face : CUBE_FACES) {
            if (cube_face.direction == TOP || cube_face.direction == DOWN)
              this->add_face_to_mesh(cube_face, block);
            if (should_draw_block_face(this, cube_face.direction, {x, y, z}))
              this->add_face_to_mesh(CUBE_FACES[cube_face.direction], block);
          }
        }
      }
    }
  }

  this->mesh = new Mesh(this->vertices, this->indices);
}

void Chunk::prepare_render() {
  this->indices = {};
  this->vertices = {};

  for (int x = 0; x < this->SIZE; x++) {
    for (int z = 0; z < this->SIZE; z++) {
      int height = this->blocks[x][z].size();
      for (int y = 0; y < height; y++) {
        Block block = this->blocks[x][z][y];
        if (!block.type->solid)
          continue;

        for (const auto &cube_face : CUBE_FACES) {
          if (cube_face.direction == TOP || cube_face.direction == DOWN)
            this->add_face_to_mesh(cube_face, block);
          if (should_draw_block_face(this, cube_face.direction, {x, y, z}))
            this->add_face_to_mesh(CUBE_FACES[cube_face.direction], block);
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

bool Chunk::in_bounds(glm::vec3 position) {
  int x = this->position.x;
  int y = this->position.y;
  int z = this->position.z;
  return x > 0 && y >= 0 && z >= 0 && x < this->SIZE && z < this->SIZE &&
         y < this->blocks[x][z].size();
}

void Chunk::set(glm::vec3 position, Block block) {
  if (in_bounds(position))
    blocks[position.x][position.z][position.y] = block;
}

Chunk *create_chunk(glm::vec3 position, struct World *world) {
  Chunk *chunk = new Chunk(position, world);
  gen(*chunk);
  return chunk;
}

void Chunk::update_neighbors() {
  this->neighbor_chunk = {};
  for (Direction dir : directions) {
    int newX = (int)this->position.x + (int)direction_offset[dir].x;
    int newZ = (int)this->position.z + (int)direction_offset[dir].z;

    Chunk *chunk = this->world->get_chunk_at(newX, newZ);
    if (!chunk)
      continue;

    this->neighbor_chunk[dir] = chunk;
  }
}

void Chunk::update() {
  this->update_neighbors();
  this->prepare_render();
  this->version = this->world->version;
}

void Chunk::mark_neighbors_dirty() {
  for (Direction dir : directions) {
    int newX = (int)this->position.x + (int)direction_offset[dir].x;
    int newZ = (int)this->position.z + (int)direction_offset[dir].z;

    Chunk *chunk = this->world->get_chunk_at(newX, newZ);
    if (chunk)
      chunk->dirty = true;
  }
}

std::vector<Chunk *> Chunk::neighbors() {
  std::vector<Chunk *> neighbor_chunks;

  for (Direction dir : directions) {
    int newX = (int)this->position.x + (int)direction_offset[dir].x;
    int newZ = (int)this->position.z + (int)direction_offset[dir].z;

    Chunk *chunk = this->world->get_chunk_at(newX, newZ);
    if (chunk)
      neighbor_chunks.push_back(chunk);
  }

  return neighbor_chunks;
}
