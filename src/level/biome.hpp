/*
#include "blocks/block_type.hpp"
#include "blocks/blocks.hpp"
#include <unordered_map>

struct Biome {
  BlockType *primary_block_type;
  BlockType *secondary_block_type;
  float terrain_roughness;
  float tree_density;
  struct Decoration {
    TreeType tree_type;
  } decoration;
};

enum class BiomeType { PLAINS = 0, JUNGLE, DESERT, OCEAN, SNOW_PEAKS };

static Biome plains = {
    .primary_block_type = new Grass(),
    .secondary_block_type = new Stone(),
    .terrain_roughness = 0.05f,
    .tree_density = 0.03,
};

static Biome jungle = {.primary_block_type = new Grass(),
                       .secondary_block_type = new Stone(),
                       .terrain_roughness = 0.0035,
                       .tree_density = 0.005f,
                       .decoration = {.tree_type = TreeType::JUNGLE}};

static Biome desert = {.primary_block_type = new Sand(),
                       .secondary_block_type = new Sand(),
                       .terrain_roughness = 0.05f,
                       .tree_density = 0.0};

static Biome ocean = {
    .primary_block_type = new Sand(),
    .terrain_roughness = 0.01,
    .tree_density = 0.0,
};

static Biome snow_peaks = {
    .primary_block_type = new Snow(),
    .terrain_roughness = 0.05,
    .tree_density = 0.0,
};

static std::unordered_map<BiomeType, Biome> biomes{
    {BiomeType::PLAINS, plains},         {BiomeType::JUNGLE, jungle},
    {BiomeType::DESERT, desert},         {BiomeType::OCEAN, ocean},
    {BiomeType::SNOW_PEAKS, snow_peaks},
};
*/
