#ifndef WORLD_H
#define WORLD_H

#include "../common.hpp"
#include "../gfx/gfx.hpp"
#include "../gfx/shader.hpp"
#include "../state.hpp"
#include "../utils/position.hpp"
#include "chunk.hpp"
#include <cmath>
#include <optional>

struct PendingBlock {
  glm::ivec3 chunkPosition;
  glm::ivec3 blockPosition;
  Block *block;
};

struct World {
  World(int seed) {
    srand(seed);
    this->seed = seed;
    glm::vec3 center(0.0f);
    state.camera.position = glm::vec3(center.x, 40, center.z);
  }

  int nChunks = 6;
  int version = 1;
  int seed;

  std::vector<PendingBlock> pendingBlocks{};
  std::unordered_map<glm::ivec3, Chunk *> chunks;
  std::vector<Chunk *> chunksNeedUpdate;

  void tick();
  void render();
  void loadAndUnloadChunks();
  void prepareNewChunks(unsigned int maxThrottle);
  void putPendingBlocks(Chunk *chunk);
  void newChunkAt(glm::ivec3 chunkPosition);
  void deleteFarChunks();
  Chunk *getChunkAt(const glm::ivec3 position);
  bool isChunkFar(glm::ivec3 chunkPosition);
  Chunk *currentChunk();
  Block *blockAt(glm::vec3 globalPosition);
  void updateBlockAt(glm::vec3 globalPosition);

  Chunk *globalPositionToChunk(glm::vec3 p) {
    glm::ivec3 chunkPosition = {
        p.x < 0 ? p.x / CHUNK_SIZE - 1 : p.x / CHUNK_SIZE,
        0,
        p.z < 0 ? p.z / CHUNK_SIZE - 1 : p.z / CHUNK_SIZE,
    };
    chunkPosition.y = 0;
    return getChunkAt(chunkPosition);
  }

  glm::ivec3 globalPositionToBlockPosition(glm::vec3 gp) {
    float localX = std::fmodf(glm::floor(gp.x), CHUNK_SIZE);
    float localZ = std::fmodf(glm::floor(gp.z), CHUNK_SIZE);

    localX = fmodf(localX + CHUNK_SIZE, CHUNK_SIZE);
    localZ = fmodf(localZ + CHUNK_SIZE, CHUNK_SIZE);

    return glm::ivec3(localX, glm::floor(gp.y), localZ);
  }

  glm::vec3 globalPositionToFloatBlockPosition(glm::vec3 globalPosition) {
    float localX = std::fmodf(globalPosition.x, CHUNK_SIZE);
    float localZ = std::fmodf(globalPosition.z, CHUNK_SIZE);

    localX = fmodf(localX + CHUNK_SIZE, CHUNK_SIZE);
    localZ = fmodf(localZ + CHUNK_SIZE, CHUNK_SIZE);

    return glm::vec3(localX, globalPosition.y, localZ);
  }

  std::optional<Block *> globalPositionToBlock(glm::vec3 globalPosition) {
    Chunk *chunk = globalPositionToChunk(globalPosition);
    if (chunk == nullptr)
      return std::nullopt;

    glm::ivec3 blockPosition = globalPositionToBlockPosition(globalPosition);

    Block *block = chunk->getBlock(blockPosition);
    if (block != nullptr)
      return block;

    return std::nullopt;
  }
};

#endif
