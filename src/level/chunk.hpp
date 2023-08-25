#pragma once

#include "../common.hpp"
#include "../state.hpp"
#include "../utils/math.hpp"
#include "blocks/blocks.hpp"
#include "direction.hpp"
#include "mesh.hpp"

static glm::vec3 CUBE_F_B_VERTICES[] = {
    glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0.5, -0.5, 0.5),
    glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5)};

static glm::vec3 CUBE_L_R_VERTICES[] = {
    glm::vec3(-0.5, -0.5, -0.5), glm::vec3(-0.5, 0.5, -0.5),
    glm::vec3(-0.5, -0.5, 0.5), glm::vec3(-0.5, 0.5, 0.5)};

static glm::vec3 CUBE_T_B_VERTICES[] = {
    glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0.5, 0.5, -0.5),
    glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5)};

static std::vector<std::vector<unsigned int>> QUAD_FACE_INDICES{
    {2, 1, 0, 1, 2, 3}, {0, 1, 2, 1, 3, 2}, {0, 1, 2, 1, 3, 2},
    {2, 1, 0, 2, 3, 1}, {2, 1, 0, 2, 3, 1}, {0, 1, 2, 3, 2, 1},
};

struct CubeFace {
  int ID;
  enum Direction direction;
  glm::vec3 position;

  glm::vec3 *vertices() {
    switch (direction) {
    case TOP:
      return CUBE_T_B_VERTICES;
    case NORTH:
    case SOUTH:
      return CUBE_F_B_VERTICES;
    case WEST:
    case EAST:
      return CUBE_L_R_VERTICES;
    case DOWN:
      return CUBE_T_B_VERTICES;
    }
  }
};

const glm::vec3 DIRECTIONS[] = {glm::vec3(0, 1, 0),  glm::vec3(0, 0, 1),
                                glm::vec3(1, 0, 0),  glm::vec3(-1, 0, 0),
                                glm::vec3(0, 0, -1), glm::vec3(0, -1, 0)};

static const std::vector<CubeFace> CUBE_FACES{
    {0, TOP, glm::vec3(1, 1, 1)},    {1, SOUTH, glm::vec3(1, 1, 1)},
    {2, WEST, glm::vec3(-1, 1, 1)},  {3, EAST, glm::vec3(1, 1, 1)},
    {4, NORTH, glm::vec3(1, 1, -1)}, {5, DOWN, glm::vec3(1, -1, 1)},
};

struct Block {
  BlockType *type;
  // glm::vec3 position;
};

struct Chunk {
  struct World *world;
  int version = 1;
  glm::vec3 position;

  int SIZE = 16;

  bool dirty = false;

  std::vector<size_t> mesh_border_indexes;
  std::vector<std::vector<Vertex>> vertices;
  std::vector<std::vector<unsigned int>> indices;

  Mesh *mesh;
  std::vector<std::vector<std::vector<Block>>> blocks;
  std::map<Direction, Chunk*> neighbor_chunk{};


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
  std::vector<Chunk*> neighbors();

  bool in_bounds(glm::ivec3 position);
  bool is_border(int x, int z);
  void mark_neighbors_dirty();

  Block *get_neighbor_block(Direction direction, glm::vec3 position);
  Block *get_block(int x, int y, int z);
  ~Chunk() {
    this->blocks.clear();
    this->blocks.shrink_to_fit();
    this->indices.clear();
    this->indices.shrink_to_fit();
    this->vertices.clear();
    this->vertices.shrink_to_fit();
    delete this->mesh;
  }
};

Chunk *create_chunk(glm::vec3 position, struct World *world);
