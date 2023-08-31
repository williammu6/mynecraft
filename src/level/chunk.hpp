#ifndef CHUNK_H
#define CHUNK_H

#include "../common.hpp"
#include "../state.hpp"
#include "../utils/math.hpp"
#include "blocks/blocks.hpp"
#include "chunkmesh.hpp"

struct Block {
  BlockType *type;
};

struct Chunk {
  struct World *world;
  int version = 1;
  int SIZE = 16;
  glm::vec3 position;

  ChunkMesh *mesh;
  std::vector<std::vector<std::vector<Block>>> blocks;
  std::map<Direction, Chunk *> neighbor_chunk{};

  Chunk(glm::vec3 position, struct World *world) {
    this->position = position;
    this->world = world;

    this->init();
  };

  void init();
  void prepare_render();
  void prepare_render_borders();
  void prepare_block(Block &block);
  void prepare_face(CubeFace cf, Block element);
  void add_face_to_mesh(CubeFace cf, glm::vec3 position);
  void set(glm::ivec3 position, Block block);
  void render();
  void update();
  void update_neighbors();
  std::vector<Chunk *> neighbors();

  bool in_bounds(glm::ivec3 position);
  bool is_border(int x, int z);

  Block *get_neighbor_block(Direction direction, glm::vec3 position);
  Block *get_block(int x, int y, int z);
  Block *get_block(glm::ivec3 position);
  ~Chunk() {
    this->blocks.clear();
    this->blocks.shrink_to_fit();
    delete this->mesh;
  }
};

Chunk *create_chunk(glm::vec3 position, struct World *world);

#endif
