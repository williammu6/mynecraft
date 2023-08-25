#include "chunk.hpp"
#include "gen.hpp"
#include "world.hpp"

std::vector<Direction> directions{SOUTH, EAST, WEST, NORTH};

std::map<Direction, glm::vec3> direction_offset{{SOUTH, {0, 0, 1}},
                                                {NORTH, {0, 0, -1}},
                                                {WEST, {-1, 0, 0}},
                                                {EAST, {1, 0, 0}}};

void Chunk::add_face_to_mesh(CubeFace cf, glm::vec3 position) {
  Block *block = this->get_block(position.x, position.y, position.z);
  TextureAtlas *texture_atlas = state.renderer->texture_atlas;
  auto texture_offset = block->type->texture_offset(cf.direction);

  auto face_direction = DIRECTIONS[cf.ID];

  int nx = position.x + face_direction.x;
  int ny = position.y + face_direction.y;
  int nz = position.z + face_direction.z;

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

  std::vector<Vertex> tmp_vertices;

  this->vertices.push_back(
      {{V[0] * cf.position + position, face_direction, glm::vec2(minTX, minTY)},
       {V[1] * cf.position + position, face_direction, glm::vec2(maxTX, minTY)},
       {V[2] * cf.position + position, face_direction, glm::vec2(minTX, maxTY)},
       {V[3] * cf.position + position, face_direction,
        glm::vec2(maxTX, maxTY)}});
  this->indices.push_back(QUAD_FACE_INDICES[cf.ID]);
}

void Chunk::render() {
  this->mesh->draw((glm::vec3)this->position * (float)this->SIZE);
}

void Chunk::init() {
  this->blocks.resize(this->SIZE);
  for (int i = 0; i < this->SIZE; i++)
    this->blocks[i].resize(this->SIZE);
}

Block *Chunk::get_neighbor_block(Direction direction, glm::vec3 position) {
  int x = position.x;
  int y = position.y;
  int z = position.z;

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
  Block *neigh_block = chunk->get_neighbor_block(direction, position);
  return neigh_block == nullptr || !neigh_block->type->solid;
}

void Chunk::prepare_render_borders() {}

bool Chunk::is_border(int x, int z) {
  return x == 0 || x == SIZE - 1 || z == 0 || z == SIZE - 1;
}

void Chunk::prepare_render() {
  this->indices = {};
  this->vertices = {};

  for (int x = 0; x < this->SIZE; x++) {
    for (int z = 0; z < this->SIZE; z++) {
      int height = this->blocks[x][z].size();
      for (int y = 0; y < height; y++) {
        Block *block = this->get_block(x, y, z);
        if (!block->type->solid)
          continue;

        for (const auto &cube_face : CUBE_FACES) {
          if (cube_face.direction == TOP || cube_face.direction == DOWN)
            this->add_face_to_mesh(cube_face, {x, y, z});
          if (should_draw_block_face(this, cube_face.direction, {x, y, z}))
            this->add_face_to_mesh(CUBE_FACES[cube_face.direction], {x, y, z});
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

bool Chunk::in_bounds(glm::ivec3 p) {
  int x = p.x;
  int y = p.y;
  int z = p.z;
  bool ok = x >= 0 && y >= 0 && z >= 0 && x < SIZE && z < SIZE &&
            y < blocks[x][z].size();

  return ok;
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

    if (block.type->name == "leaves") {
      printf("Outtabounds position %d %d %d\n", block_position.x,
             block_position.y, block_position.z);
      printf("Outtabounds block %d %d %d\n", out_bounds_block_position.x,
             out_bounds_block_position.y, out_bounds_block_position.z);
      printf("Outtabounds chunk %d %d %d\n", out_bounds_chunk_position.x,
             out_bounds_chunk_position.y, out_bounds_chunk_position.z);
      printf("------------------------------------\n");
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
  gen(chunk);
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
  this->prepare_render_borders();
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
