#ifndef GEN_H
#define GEN_H

#include "chunk.hpp"
#include "perlin_noise.hpp"
#include "tree.hpp"

constexpr int MAX_WORLD_HEIGHT = 50;
constexpr int WATER_LEVEL = 0;

void gen(Chunk *chunk, int worldSeed);

#endif
