#pragma once

#include "../../blocks/blocks.hpp"
#include "../../common.hpp"
#include "../../state.hpp"
#include "../../utils/math.hpp"
#include "mesh.hpp"
#include "perlin_noise.hpp"

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
  enum Face face;
  glm::vec3 position;

  glm::vec3 *vertices() {
    switch (face) {
    case TOP:
      return CUBE_T_B_VERTICES;
    case FRONT:
    case BACK:
      return CUBE_F_B_VERTICES;
    case LEFT:
    case RIGHT:
      return CUBE_L_R_VERTICES;
    case BOTTOM:
      return CUBE_T_B_VERTICES;
    }
  }
};

const glm::vec3 DIRECTIONS[] = {glm::vec3(0, 1, 0),  glm::vec3(0, 0, 1),
                                glm::vec3(1, 0, 0),  glm::vec3(-1, 0, 0),
                                glm::vec3(0, 0, -1), glm::vec3(0, -1, 0)};

enum Direction {
  TOP_ = 0,
  SOUTH,
  EAST,
  WEST,
  NORTH,
  DOWN,
};


static const std::vector<CubeFace> CUBE_FACES{
    {0, TOP, glm::vec3(1, 1, 1)},   {1, FRONT, glm::vec3(1, 1, 1)},
    {2, LEFT, glm::vec3(-1, 1, 1)}, {3, RIGHT, glm::vec3(1, 1, 1)},
    {4, BACK, glm::vec3(1, 1, -1)}, {5, BOTTOM, glm::vec3(1, -1, 1)},
};

struct Block {
  BlockType *type;
  glm::vec3 position;
};

struct Chunk {
  struct World *world;

  glm::vec3 position;

  int SIZE = 16;
  std::vector<std::vector<Vertex>> vertices;
  std::vector<std::vector<unsigned int>> indices;

  Mesh *mesh;

  int seaLevel = 64;
  unsigned int vao, vbo, ebo;
  std::vector<std::vector<std::vector<Block>>> blocks;

  Chunk(glm::vec3 position, struct World *world) {
    this->position = position;
    this->world = world;

    this->init();
  };

  void init();

  void prepare_render();
  void prepare_block(Block &block);
  void prepare_face(CubeFace cf, Block element);
  void add_face_to_mesh(CubeFace cf, Block &block);
  bool should_draw_block(int x, int y, int z);
  Block *get_block(int x, int y, int z);
  bool in_bounds(glm::vec3 position);
  void set(glm::vec3 position, Block block);
  void generate();
  void render();

  Chunk *get_neighbor_chunk(Direction direction);
  Block *get_neighbor_block(Direction direction, Block *block);
};

Chunk *create_chunk(glm::vec3 position, struct World *world);
