#ifndef GEN_H
#define GEN_H

#include "biome.hpp"
#include "chunk.hpp"
#include "perlin_noise.hpp"
#include "tree.hpp"

constexpr int MAX_WORLD_HEIGHT = 64;
constexpr int WATER_LEVEL = 10;

void gen(Chunk *chunk, int world_seed);

Biome get_biome(float temperature, float rainfall, float elevation);

#endif
