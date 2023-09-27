#ifndef CHUNK_H
#define CHUNK_H

#include "../common.hpp"
#include "../state.hpp"
#include "../utils/math.hpp"
#include "../utils/position.hpp"
#include "blocks/blocks.hpp"
#include "chunkmesh.hpp"
#include <unordered_map>

struct Chunk {
  Chunk(glm::vec3 position, struct World *world) {
    this->position = position;
    this->world = world;
    this->mesh = nullptr;
    this->blocks = {};
  };
  ~Chunk() {
    this->neighbor_chunk = {};
    this->neighbor_chunk.clear();
    this->blocks = {};
  }

  int version = 1;
  int SIZE = 16;
  glm::vec3 position;

  std::unique_ptr<ChunkMesh> mesh;
  struct World *world;
  std::unordered_map<glm::ivec3, Block *> blocks{};
  std::map<Direction, Chunk *> neighbor_chunk{};
  void prepare_render();
  void prepare_render_borders();

  // TODO should live somewhere else
  void prepare_block(Block &block);
  void prepare_face(CubeFace cf, Block element);
  void add_face_to_mesh(CubeFace cf, glm::vec3 position);
  // TODO end should live somewhere else

  void set(glm::ivec3 position, Block *block);
  void render();
  void update();
  void update_neighbors();
  std::vector<Chunk *> neighbors();

  bool in_bounds(glm::ivec3 position);
  bool is_border(int x, int z);

  Block *get_neighbor_block(Direction direction, glm::ivec3 position);
  Block *get_block(int x, int y, int z);
  Block *get_block(glm::ivec3 position);
};

Chunk *create_chunk(glm::vec3 position, struct World *world);

#endif
