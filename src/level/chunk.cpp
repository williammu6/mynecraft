#include "chunk.hpp"
#include "chunkmesh.hpp"
#include "gen.hpp"
#include "world.hpp"

std::vector<Direction> directions{SOUTH, EAST, WEST, NORTH};

std::map<Direction, glm::vec3> direction_offset{{SOUTH, {0, 0, 1}},
                                                {NORTH, {0, 0, -1}},
                                                {WEST, {-1, 0, 0}},
                                                {EAST, {1, 0, 0}}};

void Chunk::render() {
  this->mesh->draw((glm::vec3)this->position * (float)this->SIZE,
                   &state.renderer->textures[TextureID::ATLAS]);
}

void Chunk::init() {
  this->mesh = new ChunkMesh();
  this->blocks.resize(this->SIZE);
  for (int i = 0; i < this->SIZE; i++)
    this->blocks[i].resize(this->SIZE);
}

Block *Chunk::get_neighbor_block(Direction direction, glm::vec3 pos) {
  if (in_bounds(pos + DIRECTIONS[direction]))
    return get_block(pos + DIRECTIONS[direction]);

  if (direction == NORTH && neighbor_chunk[NORTH])
    return &neighbor_chunk[NORTH]->blocks[pos.x][SIZE - 1][pos.y];
  if (direction == SOUTH && neighbor_chunk[SOUTH])
    return &neighbor_chunk[SOUTH]->blocks[pos.x][0][pos.y];
  if (direction == EAST && neighbor_chunk[EAST])
    return &neighbor_chunk[EAST]->blocks[0][pos.z][pos.y];
  if (direction == WEST && neighbor_chunk[WEST])
    return &neighbor_chunk[WEST]->blocks[SIZE - 1][pos.z][pos.y];

  return NULL;
}

bool should_draw_block_face(Chunk *chunk, Direction direction,
                            glm::vec3 position) {
  Block *neigh_block = chunk->get_neighbor_block(direction, position);
  return !neigh_block || !neigh_block->type->solid ||
         neigh_block->type->transparent;
}

bool Chunk::is_border(int x, int z) {
  return x == 0 || x == SIZE - 1 || z == 0 || z == SIZE - 1;
}

void Chunk::prepare_render() {
  this->mesh->clean();
  for (int x = 0; x < this->SIZE; x++) {
    for (int z = 0; z < this->SIZE; z++) {
      int height = this->blocks[x][z].size();
      for (int y = 0; y < height; y++) {
        glm::ivec3 block_position(x, y, z);
        Block *block = this->get_block(block_position);
        if (!block->type->solid)
          continue;

        for (const auto &cube_face : CUBE_FACES) {
          glm::vec2 texture_offset =
              block->type->texture_offset(cube_face.direction);

          if (should_draw_block_face(this, cube_face.direction, block_position))
            this->mesh->add_face(CUBE_FACES[cube_face.direction],
                                 block_position, texture_offset);
        }
      }
    }
  }
  this->mesh->setup();
}

Block *Chunk::get_block(int x, int y, int z) {
  if (this->in_bounds({x, y, z})) {
    return &this->blocks[x][z][y];
  }

  return nullptr;
}

Block *Chunk::get_block(glm::ivec3 p) { return &this->blocks[p.x][p.z][p.y]; }

bool Chunk::in_bounds(glm::ivec3 p) {
  int x = p.x;
  int y = p.y;
  int z = p.z;
  return x >= 0 && y >= 0 && z >= 0 && x < SIZE && z < SIZE &&
         y < blocks[x][z].size();
}

void Chunk::set(glm::ivec3 block_position, Block block) {
  if (in_bounds(block_position))
    blocks[(int)block_position.x][(int)block_position.z]
          [(int)block_position.y] = block;
  else {
    glm::ivec3 out_bounds_chunk_position = this->position;
    glm::ivec3 out_bounds_block_position = block_position;

    out_bounds_block_position.y = block_position.y;
    out_bounds_chunk_position.y = this->position.y;
    if (block_position.x < 0) {
      out_bounds_block_position.x = SIZE - abs(block_position.x);
      out_bounds_chunk_position.x--;
    } else if (block_position.x >= SIZE) {
      out_bounds_block_position.x = block_position.x % SIZE;
      out_bounds_chunk_position.x++;
    }
    if (block_position.z < 0) {
      out_bounds_block_position.z = SIZE - abs(block_position.z);
      out_bounds_chunk_position.z--;
    } else if (block_position.z >= SIZE) {
      out_bounds_block_position.z = block_position.z % SIZE;
      out_bounds_chunk_position.z++;
    }

    OutOfBoundsBlock outta_bounds_block = {
        .chunk_position = out_bounds_chunk_position,
        .block_position = out_bounds_block_position,
        .block = block};

    this->world->out_bounds_blocks.push_back(outta_bounds_block);
  }
}

Chunk *create_chunk(glm::vec3 position, struct World *world) {
  Chunk *chunk = new Chunk(position, world);
  gen(chunk, world->seed);
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
