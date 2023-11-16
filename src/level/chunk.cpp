#include "chunk.hpp"
#include "chunkmesh.hpp"
#include "gen.hpp"
#include "world.hpp"

std::vector<Direction> directions{SOUTH, EAST, WEST, NORTH};

std::map<Direction, glm::vec3> directionOffset{{SOUTH, {0, 0, 1}},
                                               {NORTH, {0, 0, -1}},
                                               {WEST, {-1, 0, 0}},
                                               {EAST, {1, 0, 0}}};

Block *Chunk::getNeighborBlock(Direction direction, glm::ivec3 pos) {
  if (inBounds(pos + DIRECTIONS[direction])) {
    return this->getBlock(pos + DIRECTIONS[direction]);
  }

  if (direction == NORTH)
    pos.z = SIZE - 1;
  else if (direction == SOUTH)
    pos.z = 0;
  else if (direction == EAST)
    pos.x = 0;
  else if (direction == WEST)
    pos.x = SIZE - 1;

  if (neighborChunk[direction])
    return neighborChunk[direction]->getBlock(pos);

  return NULL;
}

bool shouldDrawBlockFace(Chunk *chunk, Direction direction,
                         glm::vec3 position) {
  Block *neigh_block = chunk->getNeighborBlock(direction, position);
  if (!neigh_block)
    return true;

  if (neigh_block->liquid && !chunk->getBlock(position)->liquid)
    return true;

  return !neigh_block->drawable() || neigh_block->transparent;
}

bool Chunk::isBorder(int x, int z) {
  return x == 0 || x == SIZE - 1 || z == 0 || z == SIZE - 1;
}

void Chunk::render() {
  this->mesh->draw((glm::vec3)this->position * (float)this->SIZE,
                   &state.renderer->textures[TextureID::ATLAS]);
}

void Chunk::prepareRender() {
  this->mesh = std::make_unique<ChunkMesh>();

  for (const auto &[blockPosition, block] : blocks) {
    block->rendered = false;
    if (!block->drawable())
      continue;

    RenderType render_type =
        block->liquid ? RenderType::TRANSPARENT : RenderType::NORMAL;

    for (const auto &cube_face : CUBE_FACES) {
      glm::vec2 textureOffset = block->textureOffset(cube_face.direction);

      if (shouldDrawBlockFace(this, cube_face.direction, blockPosition))
        this->mesh->add_face(CUBE_FACES[cube_face.direction], blockPosition,
                             textureOffset, render_type, block->rotation);
      block->rendered = true;
    }
  }
  this->mesh->setup();
}

Block *Chunk::getBlock(const glm::ivec3 blockPosition) {
  return this->blocks.find(blockPosition) != this->blocks.end()
             ? this->blocks.at(blockPosition)
             : nullptr;
}

bool Chunk::inBounds(glm::ivec3 p) {
  return p.x >= 0 && p.y >= 0 && p.z >= 0 && p.x < SIZE && p.z < SIZE &&
         p.y < MAX_WORLD_HEIGHT;
}

void Chunk::set(glm::ivec3 blockPosition, Block *block) {
  if (inBounds(blockPosition))
    blocks[blockPosition] = block;
  else {
    /*
    glm::ivec3 outBoundsChunkPosition = this->position;
    glm::ivec3 outBoundsBlockPosition = blockPosition;

    outBoundsBlockPosition.y = blockPosition.y;
    outBoundsChunkPosition.y = this->position.y;
    if (blockPosition.x < 0) {
      outBoundsBlockPosition.x = SIZE - abs(blockPosition.x);
      outBoundsChunkPosition.x--;
    } else if (blockPosition.x >= SIZE) {
      outBoundsBlockPosition.x = blockPosition.x % SIZE;
      outBoundsChunkPosition.x++;
    }
    if (blockPosition.z < 0) {
      outBoundsBlockPosition.z = SIZE - abs(blockPosition.z);
      outBoundsChunkPosition.z--;
    } else if (blockPosition.z >= SIZE) {
      outBoundsBlockPosition.z = blockPosition.z % SIZE;
      outBoundsChunkPosition.z++;
    }

    PendingBlock pending_block = {.chunkPosition = outBoundsChunkPosition,
                                  .blockPosition = outBoundsBlockPosition,
                                  .block = block};

    this->world->pendingBlocks.push_back(pending_block);
    */
  }
}

Chunk *createChunk(glm::vec3 position, struct World *world) {
  Chunk *chunk = new Chunk(position, world);
  gen(chunk, world->seed);
  return chunk;
}

void Chunk::updateNeighbors() {
  this->neighborChunk = {};
  for (Direction dir : directions) {
    int newX = (int)this->position.x + (int)directionOffset[dir].x;
    int newZ = (int)this->position.z + (int)directionOffset[dir].z;

    Chunk *chunk = this->world->getChunkAt({newX, 0, newZ});
    if (!chunk)
      continue;

    this->neighborChunk[dir] = chunk;
  }
}

void Chunk::update() {
  this->updateNeighbors();
  this->prepareRender();
  this->version = this->world->version;
}

std::vector<Chunk *> Chunk::neighbors() {
  std::vector<Chunk *> neighborChunks;

  for (Direction dir : directions) {
    int newX = (int)this->position.x + (int)directionOffset[dir].x;
    int newZ = (int)this->position.z + (int)directionOffset[dir].z;

    Chunk *chunk = this->world->getChunkAt({newX, 0, newZ});
    if (chunk)
      neighborChunks.push_back(chunk);
  }

  return neighborChunks;
}
