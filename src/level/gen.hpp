#ifndef GEN_H
#define GEN_H

// #include "biome.hpp"
#include "chunk.hpp"
#include "perlin_noise.hpp"
#include "tree.hpp"

constexpr int MAX_WORLD_HEIGHT = 128;
constexpr int WATER_LEVEL = 64;

void gen(Chunk *chunk, int world_seed);

#endif
