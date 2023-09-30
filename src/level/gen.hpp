#ifndef GEN_H
#define GEN_H

#include "chunk.hpp"
#include "perlin_noise.hpp"
#include "tree.hpp"

constexpr int MAX_WORLD_HEIGHT = 64;
constexpr int WATER_LEVEL = 24;

void gen(Chunk *chunk, int world_seed);

#endif
