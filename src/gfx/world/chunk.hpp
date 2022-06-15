#pragma once

#include "../../common.hpp"
#include "../../state.hpp"
#include "../shader.hpp"
#include "../texture.hpp"
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
  enum Face face;
  glm::vec3 position;

  glm::vec3 *vertices() {
    switch (face) {
    case TOP:
      return CUBE_T_B_VERTICES;
    case FRONT_BACK:
      return CUBE_F_B_VERTICES;
    case LEFT_RIGHT:
      return CUBE_L_R_VERTICES;
    case BOTTOM:
      return CUBE_T_B_VERTICES;
    }
  }
};

const glm::vec3 DIRECTIONS[] = {glm::vec3(0, 1, 0),  glm::vec3(0, 0, 1),
                                glm::vec3(1, 0, 0),  glm::vec3(-1, 0, 0),
                                glm::vec3(0, 0, -1), glm::vec3(0, -1, 0)};

static const std::vector<CubeFace> CUBE_FACES{
    {0, TOP, glm::vec3(1, 1, 1)},         {1, FRONT_BACK, glm::vec3(1, 1, 1)},
    {2, LEFT_RIGHT, glm::vec3(-1, 1, 1)}, {3, LEFT_RIGHT, glm::vec3(1, 1, 1)},
    {4, FRONT_BACK, glm::vec3(1, 1, -1)}, {5, BOTTOM, glm::vec3(1, -1, 1)},
};

struct Block {
  BlockType *type;
  glm::vec3 position;
};

struct Chunk {
  Shader *shader;
  TextureAtlas *texture_atlas;
  glm::vec3 position;

  int size = 3;
  std::vector<std::vector<Vertex>> vertices;
  std::vector<std::vector<unsigned int>> indices;

  Mesh *mesh;

  int seaLevel = 64;
  unsigned int vao, vbo, ebo;
  std::vector<std::vector<std::vector<Block>>> blocks;

  Chunk(Shader *shader, TextureAtlas *texture_atlas, glm::vec3 position) {
    this->shader = shader;
    this->position = position;
    this->texture_atlas = texture_atlas;

    this->init();
  };

  void init();

  void prepare_render();
  void prepare_block(Block &block);
  void prepare_face(CubeFace cf, Grass element);
  void add_face_to_mesh(CubeFace cf, Block &block);

  void render();
};
