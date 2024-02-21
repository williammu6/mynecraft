#ifndef GEN_H
#define GEN_H

#include "chunk.hpp"
#include "perlin_noise.hpp"

struct Chunk;

#define MAX_WORLD_HEIGHT 128
#define WATER_LEVEL 32
#define SNOW_LEVEL 100

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
