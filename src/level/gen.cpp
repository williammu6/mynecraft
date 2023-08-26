#include "gen.hpp"
#include "blocks/cobblestone.hpp"

#define MAX_HEIGHT 64

void gen(Chunk *chunk) {
  BlockType *block_type = nullptr;

  const siv::PerlinNoise::seed_type seed = 2u;
  const siv::PerlinNoise perlin{seed};
  srand(time(NULL));

  for (int x = 0; x < chunk->SIZE; x++) {
    for (int z = 0; z < chunk->SIZE; z++) {
      for (int y = 0; y < 64; y++) {
        chunk->blocks[x][z].push_back({new Air()});
      }
    }
  }

  for (int x = 0; x < chunk->SIZE; x++) {
    int nX = (x + 1) + chunk->position.x * chunk->SIZE;

    for (int z = 0; z < chunk->SIZE; z++) {
      int nZ = (z + 1) + chunk->position.z * chunk->SIZE;
      const double noise = perlin.octave2D_01(nX * 0.01, nZ * 0.01, 4);
      int height = glm::max(1, (int)(noise * MAX_HEIGHT));

      if (height < 10) {
        block_type = new Water();
      } else if (height < 14) {
        block_type = new Sand();
      } else if (height < MAX_HEIGHT) {
        block_type = new Grass();
      } else {
        block_type = new Snow();
      }

      for (int y = 0; y < height; y++) {
        glm::ivec3 position = {x, y, z};
        chunk->set(position, {block_type});
      }
      if (RANDCHANCE(0.01) && strcmp(block_type->name, "sand") == 0) {
        for (int cY = height; cY < height + RAND(3, 5); cY++) {
          glm::ivec3 cactus_position = {x, cY, z};
          chunk->set(cactus_position, {new Cactus()});
        }
      }
      if (RANDCHANCE(0.015) && strcmp(block_type->name, "grass") == 0) {
        create_tree(chunk, {x, height, z});
      }
    }
  }
}
