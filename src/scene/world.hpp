#ifndef WORLD_H
#define WORLD_H

#include "chunk.hpp"
#include "world_generator.hpp"

struct WorldGenerator;
struct Chunk;

struct World {
public:
  World(int seed) {
    generator = std::make_unique<WorldGenerator>(seed);
  }
  ~World() {
  }

  int version = 1;

  glm::ivec3 globalPositionToBlockPosition(glm::vec3 gp);
  std::optional<Block *> globalPositionToBlock(glm::vec3 globalPosition);
  std::optional<Chunk *> getChunkAt(const glm::ivec3 position);
  std::optional<Chunk *> globalPositionToChunk(glm::vec3 p);
  std::unique_ptr<WorldGenerator> generator;
  std::vector<Chunk *> chunksNeedUpdate;

  int heighestBlockAt(int globalX, int globalZ);
  bool isChunkFar(glm::ivec3 chunkPosition);
  void deleteBlockAt(glm::vec3 globalPosition);
  void newChunkAt(glm::vec3 chunkPosition);
  void placeBlockAt(glm::vec3 globalPosition, glm::vec3 faceSide, Block *block);
  void render();
  void tick();

private:
  int chunkDistance = 18;

  std::unordered_map<glm::ivec3, Chunk *> chunks;

  void deleteFarChunks();
  void loadAndUnloadChunks();
  void prepareNewChunks(unsigned int maxReloads);
};

#endif
