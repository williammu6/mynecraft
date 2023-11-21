#ifndef CHUNK_H
#define CHUNK_H

#include "../common.hpp"
#include "../state.hpp"
#include "../utils/math.hpp"
#include "../utils/position.hpp"
#include "blocks/blocks.hpp"
#include "chunkmesh.hpp"

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

  int version = 1;
  glm::vec3 position;

  std::map<Direction, std::optional<Chunk *>> neighborChunk{};
  std::optional<Block *> getBlock(const glm::ivec3 blockPosition);
  std::optional<Block *> getNeighborBlock(Direction direction, glm::ivec3 pos);
  std::unique_ptr<ChunkMesh> chunkmesh;
  std::unordered_map<glm::ivec3, Block *> blocks{};
  std::vector<std::optional<Chunk *>> neighbors();

  struct World *world;

  bool inBounds(glm::ivec3 position);

  void addFaceToMesh(CubeFace cf, glm::vec3 position);
  void deleteBlockAt(glm::ivec3 position);
  void prepareBlock(Block &block);
  void prepareFace(CubeFace cf, Block element);
  void prepareRender();
  void prepareRenderBorders();
  void render();
  void set(glm::ivec3 position, Block *block);
  void update();
  void updateNeighbors();
};

Chunk *createChunk(glm::vec3 position, struct World *world);

#endif
