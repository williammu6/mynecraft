#ifndef CHUNK_H
#define CHUNK_H

#include "../utils/position.hpp"
#include "blocks/blocks.hpp"
#include "chunkmesh.hpp"
#include "world.hpp"

#define CHUNK_SIZE 16

struct Chunk {
  Chunk(glm::vec3 position, struct World *world)
      : position(position), world(world) {
    chunkmesh = nullptr;
    blocks = {};
  };
  ~Chunk() {
    neighborChunk.clear();
    blocks.clear();
  }

  glm::vec3 position;
  World *world;

  std::map<Direction, std::optional<Chunk *>> neighborChunk{};
  std::optional<Block *> getBlock(const glm::ivec3 blockPosition);
  std::optional<Block *> getNeighborBlock(Direction direction, glm::ivec3 pos);
  std::unique_ptr<ChunkMesh> chunkmesh;
  std::unordered_map<glm::ivec3, Block *> blocks{};
  std::vector<Chunk *> neighbors();

  bool inBounds(glm::ivec3 position);
  float getLocalLight(glm::ivec3 blockPosition);
  void prepareRenderBorders();
  void reloadMesh();
  void render();
  void set(glm::ivec3 position, Block *block);
  void update();
  void updateNeighbors();
};

#endif
