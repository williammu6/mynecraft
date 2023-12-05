#ifndef GEN_H
#define GEN_H

#include "chunk.hpp"
#include "perlin_noise.hpp"

struct Chunk;

constexpr int MAX_WORLD_HEIGHT = 96;
constexpr int WATER_LEVEL = 48;

struct WorldGenerator {
  int seed;

  void generateChunk(Chunk *chunk);

  siv::PerlinNoise perlin;

  WorldGenerator(unsigned int seed) : seed(seed) {
    srand(seed);
    perlin = siv::PerlinNoise(seed);
  };

  void createTree(Chunk *chunk, glm::ivec3 position, TreeType treeType);
  void createCactus(Chunk *chunk, glm::ivec3 position);
};

#endif
