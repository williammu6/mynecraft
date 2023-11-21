#ifndef WORLD_H
#define WORLD_H

#include "../common.hpp"
#include "../gfx/gfx.hpp"
#include "../gfx/shader.hpp"
#include "../state.hpp"
#include "../utils/position.hpp"
#include "chunk.hpp"
#include "world_generator.hpp"

class World {
public:
  World(int seed) {
    state.camera.position = glm::vec3(0.0f, 60, 0.0f);
    generator = std::make_unique<WorldGenerator>(seed);
  }
  ~World() {
  }

  int version = 1;
  std::unique_ptr<WorldGenerator> generator;

  void tick();
  void render();
  void newChunkAt(glm::ivec3 chunkPosition);

  bool isChunkFar(glm::ivec3 chunkPosition);

  std::optional<Chunk *> getChunkAt(const glm::ivec3 position);
  std::optional<Chunk *> globalPositionToChunk(glm::vec3 p);
  std::optional<Block *> globalPositionToBlock(glm::vec3 globalPosition);

  glm::ivec3 globalPositionToBlockPosition(glm::vec3 gp);
  std::vector<Chunk *> chunksNeedUpdate;

private:
  int nChunks = 4;

  std::unordered_map<glm::ivec3, Chunk *> chunks;

  void deleteFarChunks();
  void loadAndUnloadChunks();
  void prepareNewChunks(unsigned int maxThrottle);
};

#endif
