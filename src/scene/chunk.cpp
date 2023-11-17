#include "chunk.hpp"
#include "chunkmesh.hpp"
#include "gen.hpp"
#include "world.hpp"

std::vector<Direction> directions{SOUTH, EAST, WEST, NORTH};

std::map<Direction, glm::vec3> directionOffset{{SOUTH, {0, 0, 1}},
                                               {NORTH, {0, 0, -1}},
                                               {WEST, {-1, 0, 0}},
                                               {EAST, {1, 0, 0}}};

std::optional<Block *> Chunk::getNeighborBlock(Direction direction,
                                               glm::ivec3 pos) {
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

  if (neighborChunk[direction].has_value())
    return neighborChunk[direction].value()->getBlock(pos);
  return std::nullopt;
}

bool shouldDrawBlockFace(Chunk *chunk, Direction direction,
                         glm::vec3 position) {
  auto maybeNeighborBlock = chunk->getNeighborBlock(direction, position);
  if (!maybeNeighborBlock.has_value())
    return true;

  auto neighborBlock = maybeNeighborBlock.value();

  auto maybeBlock = chunk->getBlock(position);
  if (!maybeBlock.has_value())
    return true;

  if (neighborBlock->liquid && !maybeBlock.value()->liquid)
    return true;

  return !neighborBlock->drawable() || neighborBlock->transparent;
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

std::optional<Block *> Chunk::getBlock(const glm::ivec3 blockPosition) {
  if (this->blocks.find(blockPosition) != this->blocks.end())
    return this->blocks.at(blockPosition);

  return std::nullopt;
}

bool Chunk::inBounds(glm::ivec3 p) {
  return p.x >= 0 && p.y >= 0 && p.z >= 0 && p.x < SIZE && p.z < SIZE &&
         p.y < MAX_WORLD_HEIGHT;
}

void Chunk::set(glm::ivec3 blockPosition, Block *block) {
  if (inBounds(blockPosition))
    blocks[blockPosition] = block;
}

Chunk *createChunk(glm::vec3 position, World *world) {
  Chunk *chunk = new Chunk(position, world);
  state.world->generator->generateChunk(chunk);
  return chunk;
}

void Chunk::updateNeighbors() {
  this->neighborChunk = {};
  for (Direction dir : directions) {
    int newX = (int)this->position.x + (int)directionOffset[dir].x;
    int newZ = (int)this->position.z + (int)directionOffset[dir].z;
    this->neighborChunk[dir] = this->world->getChunkAt({newX, 0, newZ});
  }
}

void Chunk::update() {
  this->updateNeighbors();
  this->prepareRender();
  this->version = this->world->version;
}

std::vector<std::optional<Chunk *>> Chunk::neighbors() {
  std::vector<std::optional<Chunk *>> neighborChunks;

  for (Direction dir : directions) {
    int newX = (int)this->position.x + (int)directionOffset[dir].x;
    int newZ = (int)this->position.z + (int)directionOffset[dir].z;
    neighborChunks.push_back(this->world->getChunkAt({newX, 0, newZ}));
  }

  return neighborChunks;
}
