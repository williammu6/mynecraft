#ifndef GEN_H
#define GEN_H

#include "chunk.hpp"
#include "perlin_noise.hpp"
#include "tree.hpp"

#define CHANCE(chance) ((RAND(0, 100000) / 100000.0) <= chance)

constexpr int MAX_WORLD_HEIGHT = 96;
constexpr int WATER_LEVEL = 32;

struct WorldGenerator {
  int seed;

  void generateChunk(Chunk *chunk);

  siv::PerlinNoise perlin;

  WorldGenerator(unsigned int seed) : seed(seed) {
    srand(seed);
    perlin = siv::PerlinNoise(seed);
  };

  void createTree(struct Chunk *chunk, glm::ivec3 position, TreeType treeType);
  void createCactus(struct Chunk *chunk, glm::ivec3 position);
};

#endif
