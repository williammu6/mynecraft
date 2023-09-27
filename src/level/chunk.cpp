#include "chunk.hpp"
#include "chunkmesh.hpp"
#include "gen.hpp"
#include "world.hpp"

std::vector<Direction> directions{SOUTH, EAST, WEST, NORTH};

std::map<Direction, glm::vec3> direction_offset{{SOUTH, {0, 0, 1}},
                                                {NORTH, {0, 0, -1}},
                                                {WEST, {-1, 0, 0}},
                                                {EAST, {1, 0, 0}}};

Block *Chunk::get_neighbor_block(Direction direction, glm::ivec3 pos) {
  if (in_bounds(pos + DIRECTIONS[direction])) {
    return this->get_block(pos + DIRECTIONS[direction]);
  }

  if (direction == NORTH)
    pos.z = SIZE - 1;
  else if (direction == SOUTH)
    pos.z = 0;
  else if (direction == EAST)
    pos.x = 0;
  else if (direction == WEST)
    pos.x = SIZE - 1;

  if (neighbor_chunk[direction])
    return neighbor_chunk[direction]->get_block(pos);

  return NULL;
}

bool should_draw_block_face(Chunk *chunk, Direction direction,
                            glm::vec3 position) {
  Block *neigh_block = chunk->get_neighbor_block(direction, position);
  if (!neigh_block)
    return true;

  if (neigh_block->liquid && !chunk->get_block(position)->liquid)
    return true;

  return !neigh_block->drawable() || neigh_block->transparent;
}

bool Chunk::is_border(int x, int z) {
  return x == 0 || x == SIZE - 1 || z == 0 || z == SIZE - 1;
}

void Chunk::render() {
  this->mesh->draw((glm::vec3)this->position * (float)this->SIZE,
                   &state.renderer->textures[TextureID::ATLAS]);
}

void Chunk::prepare_render() {
  this->mesh = std::make_unique<ChunkMesh>();

  for (const auto &[block_position, block] : blocks) {
    if (!block->drawable())
      continue;

    RenderType rt =
        block->liquid ? RenderType::TRANSPARENT : RenderType::NORMAL;

    for (const auto &cube_face : CUBE_FACES) {
      glm::vec2 texture_offset = block->texture_offset(cube_face.direction);

      if (should_draw_block_face(this, cube_face.direction, block_position))
        this->mesh->add_face(CUBE_FACES[cube_face.direction], block_position,
                             texture_offset, rt);
    }
  }
  this->mesh->setup();
}

Block *Chunk::get_block(int x, int y, int z) {
  glm::ivec3 block_position(x, y, z);
  return this->blocks.find(block_position) != this->blocks.end()
             ? this->blocks.at(block_position)
             : nullptr;
}

Block *Chunk::get_block(glm::ivec3 block_position) {
  return this->blocks.find(block_position) != this->blocks.end()
             ? this->blocks.at(block_position)
             : nullptr;
}

bool Chunk::in_bounds(glm::ivec3 p) {
  return p.x >= 0 && p.y >= 0 && p.z >= 0 && p.x < SIZE && p.z < SIZE &&
         p.y < MAX_WORLD_HEIGHT;
}

void Chunk::set(glm::ivec3 block_position, Block *block) {
  if (in_bounds(block_position))
    blocks[block_position] = block;
  else {
    /*
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

    OutOfBoundsBlock outta_bounds_block = {.chunk_position =
    out_bounds_chunk_position, .block_position = out_bounds_block_position,
                                           .block = block};

    this->world->out_bounds_blocks.push_back(outta_bounds_block);
    */
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
