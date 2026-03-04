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
  const float maxShadowDistance = 15.0f;
  const float rayStep = 0.5f;
  float blockers = 0.0f;

  glm::ivec3 chunkBase = glm::ivec3(this->position) * CHUNK_SIZE;
  glm::ivec3 globalBlock = chunkBase + blockPosition;

  // Match shader light direction and cast towards the light source.
  glm::vec3 toLightDir = glm::normalize(glm::vec3(-0.5f, 0.5f, 0.0f));
  glm::vec3 samplePos = glm::vec3(globalBlock) + glm::vec3(0.5f);

  for (float dist = rayStep; dist <= maxShadowDistance; dist += rayStep) {
    samplePos += toLightDir * rayStep;
    glm::ivec3 sampleBlock = glm::ivec3(glm::floor(samplePos));

    auto maybeBlock = world->getBlockAtGlobalPosition(sampleBlock);
    if (!maybeBlock.has_value()) {
      continue;
    }

    auto block = maybeBlock.value();
    if (block->liquid || !block->drawable()) {
      continue;
    }

    // Transparent solids should dim the light, but not as much as opaque ones.
    blockers += block->transparent ? 0.45f : 1.0f;
    if (blockers >= 10.0f) {
      break;
    }
  }

  float light = 1.0f - blockers * 0.08f;
  return glm::clamp(light, 0.2f, 1.0f);
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
