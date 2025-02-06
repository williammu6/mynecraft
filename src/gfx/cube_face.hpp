#ifndef CUBE_FACE_H
#define CUBE_FACE_H

#include "Mesh/vertex.hpp"
#include <vector>

enum Direction {
  TOP = 0,
  SOUTH,
  WEST,
  EAST,
  NORTH,
  DOWN,
};

const glm::ivec3 DIRECTIONS[] = {glm::ivec3(0, 1, 0),  glm::ivec3(0, 0, 1),
                                 glm::ivec3(-1, 0, 0), glm::ivec3(1, 0, 0),
                                 glm::ivec3(0, 0, -1), glm::ivec3(0, -1, 0)};

const glm::vec3 NORMALS[] = {glm::vec3(0, 1, 0),  glm::vec3(0, 0, 1),
                             glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0),
                             glm::vec3(0, 0, -1), glm::vec3(0, 0, 0)};

static std::vector<glm::vec3> CUBE_F_B_VERTICES = {
    {-0.5, -0.5, 0.5}, {0.5, -0.5, 0.5}, {-0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}};

static std::vector<glm::vec3> CUBE_L_R_VERTICES = {
    {-0.5, -0.5, -0.5}, {-0.5, 0.5, -0.5}, {-0.5, -0.5, 0.5}, {-0.5, 0.5, 0.5}};

static std::vector<glm::vec3> CUBE_T_B_VERTICES = {
    {-0.5, 0.5, -0.5}, {0.5, 0.5, -0.5}, {-0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}};

static std::vector<std::vector<unsigned int>> QUAD_FACE_INDICES{
    {2, 1, 0, 1, 2, 3}, {0, 1, 2, 1, 3, 2}, {0, 1, 2, 1, 3, 2},
    {2, 1, 0, 2, 3, 1}, {2, 1, 0, 2, 3, 1}, {0, 1, 2, 3, 2, 1},
};

inline std::vector<glm::vec3> getVerticesByFaceDirection(enum Direction face) {
  switch (face) {
  case TOP:
  case DOWN:
    return CUBE_T_B_VERTICES;
  case SOUTH:
  case NORTH:
    return CUBE_F_B_VERTICES;
  case WEST:
  case EAST:
    return CUBE_L_R_VERTICES;
  }
}

struct CubeFace {
  enum Direction direction;
  glm::vec3 position;

  /**
   * blockVertex
   * returns a std::vector<CubeVertex>, containing Position, Normal, and uv
   */
  std::vector<CubeVertex> blockVertex(glm::vec3 blockPosition,
                                      const std::vector<glm::vec2> uvs,
                                      const float localLight) const {
    auto vertices = getVerticesByFaceDirection(direction);
    std::vector<CubeVertex> vertexList;
    for (size_t i = 0; i < 4; i++) {
      vertexList.push_back(
          (CubeVertex){.position = vertices[i] * position + blockPosition,
                       .normal = NORMALS[direction],
                       .uv = uvs[i],
                       .light = localLight});
    }
    return vertexList;
  }
};

static const std::vector<CubeFace> CUBE_FACES{
    {TOP, glm::vec3(1, 1, 1)},    {SOUTH, glm::vec3(1, 1, 1)},
    {EAST, glm::vec3(1, 1, 1)},   {WEST, glm::vec3(-1, 1, 1)},
    {NORTH, glm::vec3(1, 1, -1)}, {DOWN, glm::vec3(1, -1, 1)},
};

#endif
