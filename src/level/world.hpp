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
  Block *blockAt(glm::vec3 globalPosition);
  void updateBlockAt(glm::vec3 globalPosition);

  Chunk *globalPositionToChunk(glm::vec3 p);
  glm::ivec3 globalPositionToBlockPosition(glm::vec3 gp);
  glm::vec3 globalPositionToFloatBlockPosition(glm::vec3 globalPosition);
  std::optional<Block *> globalPositionToBlock(glm::vec3 globalPosition);
};

#endif
