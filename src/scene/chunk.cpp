#include "chunk.hpp"
#include "../state.hpp"
#include "../utils/debug.hpp"
#include "chunkmesh.hpp"
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
    pos.z = CHUNK_SIZE - 1;
  else if (direction == SOUTH)
    pos.z = 0;
  else if (direction == EAST)
    pos.x = 0;
  else if (direction == WEST)
    pos.x = CHUNK_SIZE - 1;

  if (neighborChunk[direction].has_value())
    return neighborChunk[direction].value()->getBlock(pos);
  return std::nullopt;
}

bool shouldDrawBlockFace(Chunk *chunk,
                         Direction direction,
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

void Chunk::render() {
  this->chunkmesh->draw((glm::vec3)this->position * (float)CHUNK_SIZE,
                        &state.renderer->textures[TextureID::ATLAS]);
}

void Chunk::reloadMesh() {
  this->chunkmesh = std::make_unique<ChunkMesh>();

  for (const auto &[blockPosition, block] : blocks) {
    block->rendered = false;
    if (!block->drawable())
      continue;

    RenderType renderType =
        block->liquid ? RenderType::TRANSPARENT : RenderType::NORMAL;

    // float localLight = -1;
    for (const auto &cubeFace : CUBE_FACES) {
      glm::vec2 textureOffset = block->textureOffset(cubeFace.direction);

      if (shouldDrawBlockFace(this, cubeFace.direction, blockPosition)) {
        float localLight = this->getLocalLight(blockPosition);

        this->chunkmesh->addBlockFace(CUBE_FACES[cubeFace.direction],
                                      blockPosition,
                                      textureOffset,
                                      renderType,
                                      localLight,
                                      block->rotation);
      }
      block->rendered = true;
    }
  }

  this->chunkmesh->setup();
}

float Chunk::getLocalLight(glm::ivec3 blockPosition) {
  float light = 1.0f;

  for (int y = 1; y < 15; y++) {
    for (int x = 1; x < y + 1; x++) {
      if (auto maybeBlock = this->getBlock(glm::ivec3(
              blockPosition.x + x, blockPosition.y + y, blockPosition.z))) {
        light -= 0.15;

        if (light < 0.0) {
          return 0.0f;
        }
      }
    }
  }

  return light > 0.0f ? light : 0.0f;
}

std::optional<Block *> Chunk::getBlock(const glm::ivec3 blockPosition) {
  if (this->blocks.find(blockPosition) != this->blocks.end())
    return this->blocks.at(blockPosition);

  return std::nullopt;
}

bool Chunk::inBounds(glm::ivec3 p) {
  return p.x >= 0 && p.y >= 0 && p.z >= 0 && p.x < CHUNK_SIZE &&
         p.z < CHUNK_SIZE && p.y < MAX_WORLD_HEIGHT;
}

void Chunk::set(glm::ivec3 blockPosition, Block *block) {
  if (inBounds(blockPosition))
    blocks[blockPosition] = block;
}

void Chunk::update() {
  this->updateNeighbors();
  this->reloadMesh();
}

void Chunk::updateNeighbors() {
  this->neighborChunk = {};
  for (Direction dir : directions) {
    this->neighborChunk[dir] =
        this->world->getChunkAt({this->position.x + directionOffset[dir].x,
                                 0,
                                 this->position.z + directionOffset[dir].z});
  }
}

std::vector<Chunk *> Chunk::neighbors() {
  std::vector<Chunk *> neighborChunks;

  for (Direction dir : directions) {
    if (auto maybeChunk =
            this->world->getChunkAt(position + directionOffset[dir])) {
      neighborChunks.push_back(maybeChunk.value());
    }
  }

  return neighborChunks;
}
