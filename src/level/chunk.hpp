#ifndef CHUNK_H
#define CHUNK_H

#include "../common.hpp"
#include "../state.hpp"
#include "../utils/math.hpp"
#include "../utils/position.hpp"
#include "blocks/blocks.hpp"
#include "chunkmesh.hpp"
#include <unordered_map>

#define CHUNK_SIZE 4

struct Chunk {
  Chunk(glm::vec3 position, struct World *world) {
    this->position = position;
    this->world = world;
    this->mesh = nullptr;
    this->blocks = {};
  };
  ~Chunk() {
    this->neighborChunk = {};
    this->neighborChunk.clear();
    this->blocks = {};
  }

  int version = 1;
  int SIZE = CHUNK_SIZE;
  glm::vec3 position;

  std::unique_ptr<ChunkMesh> mesh;
  struct World *world;
  std::unordered_map<glm::ivec3, Block *> blocks{};
  std::map<Direction, Chunk *> neighborChunk{};
  void prepareRender();
  void prepareRenderBorders();

  void prepareBlock(Block &block);
  void prepareFace(CubeFace cf, Block element);
  void addFaceToMesh(CubeFace cf, glm::vec3 position);

  void set(glm::ivec3 position, Block *block);
  void render();
  void update();
  void updateNeighbors();
  std::vector<Chunk *> neighbors();

  bool inBounds(glm::ivec3 position);
  bool isBorder(int x, int z);

  Block *getNeighborBlock(Direction direction, glm::ivec3 position);
  Block *getBlock(const glm::ivec3 position);
};

Chunk *createChunk(glm::vec3 position, struct World *world);

#endif
