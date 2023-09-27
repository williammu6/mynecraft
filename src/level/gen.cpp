#include "gen.hpp"
#include "../common.hpp"
#include "blocks/wood.hpp"
#include "perlin_noise.hpp"

void gen(Chunk *chunk, int world_seed) {
  Block *block = new Sand();

  const siv::PerlinNoise::seed_type seed = world_seed;
  const siv::PerlinNoise perlin{seed};

  for (int x = 0; x < chunk->SIZE; x++) {
    int nX = (x + 1) + chunk->position.x * chunk->SIZE;

    for (int z = 0; z < chunk->SIZE; z++) {
      int nZ = (z + 1) + chunk->position.z * chunk->SIZE;

      const float roughness = 0.01;
      const double octave1 =
          perlin.octave2D_01(nX * roughness, nZ * roughness, 1);
      const double octave2 =
          perlin.octave2D_01(nX * roughness, nZ * roughness, 8);

      int height =
          glm::max(1, (int)((octave1 + octave2) * MAX_WORLD_HEIGHT / 2));

      block = new Grass();
      if (height < WATER_LEVEL + 2) {
        block = new Sand();
      } else if (height < MAX_WORLD_HEIGHT * 2 / 3) {
        block = new Grass();
      } else {
        block = new Snow();
      }

      for (int y = 0; y < height; y++) {
        glm::ivec3 position = {x, y, z};
        chunk->set(position, block);
      }

      for (int y = height; y < WATER_LEVEL; y++) {
        glm::ivec3 position = {x, y, z};
        if (y == height)
          chunk->set(position, new Sand());
        else
          chunk->set(position, new Water());
      }

      if (height <= WATER_LEVEL)
        continue;

      if (RANDCHANCE(0.01) && strcmp(block->name, "sand") == 0) {
        for (int cY = height; cY < height + RAND(3, 5); cY++) {
          glm::ivec3 cactus_position = {x, cY, z};
          chunk->set(cactus_position, new Cactus());
        }
      }
      if (RANDCHANCE(0.01) && strcmp(block->name, "grass") == 0) {
        create_tree(chunk, {x, height, z}, TreeType::JUNGLE);
      }
    }
  }
}

/*
Biome get_biome(float temperature, float rainfall, float elevation) {
  if (temperature < 0.5f) { // COLD
    if (elevation > 0.6)
      return biomes.at(BiomeType::SNOW_PEAKS);

    if (elevation < 0.3 && rainfall > 0.5) {
      return biomes.at(BiomeType::JUNGLE);
    } else if (elevation < 0.6 && rainfall > 0.4) {
      return biomes.at(BiomeType::PLAINS);
    } else {
    }
  } else {

    return biomes.at(BiomeType::JUNGLE);
  }

  return biomes.at(BiomeType::PLAINS);
}
*/
