#include "gen.hpp"
#include "blocks/cobblestone.hpp"

void gen(Chunk &chunk) {
  BlockType *block_type = nullptr;

  const siv::PerlinNoise::seed_type seed = 2u;
  const siv::PerlinNoise perlin{seed};

  for (int x = 0; x < chunk.SIZE; x++) {
    int nX = (x + 1) + chunk.position.x * chunk.SIZE;
    for (int z = 0; z < chunk.SIZE; z++) {
      int nZ = (z + 1) + chunk.position.z * chunk.SIZE;
      const double noise = perlin.octave2D_01(nX * 0.01, nZ * 0.01, 4);
      int height = glm::max(1, (int)(noise * 64));

      if (height < 10) {
        block_type = new Water();
      } else if (height < 14) {
        block_type = new Sand();
      } else if (height < 96) {
        block_type = new Grass();
      } else {
        block_type = new Snow();
      }

      height = z + 5;

      if (chunk.position.x == 0) block_type = new Water();
      if (chunk.position.x == 1) block_type = new Wood();
      if (chunk.position.z == 1) block_type = new Cobblestone();

      for (int y = 0; y < height; y++) {
        chunk.blocks[x][z].push_back({block_type, glm::vec3(x, y, z)});
      }

      for (int y = height; y < 64; y++) {
        chunk.blocks[x][z].push_back({new Air(), glm::vec3(x, y, z)});
      }

      if (RANDCHANCE(0.02) && strcmp(block_type->name, "sand") == 0) {
        for (int cY = height; cY < height + RAND(3, 5); cY++) {
          glm::vec3 cactus_position = {x, cY, z};
          chunk.set(cactus_position, {new Cactus(), cactus_position});
        }
      }

      if (RANDCHANCE(0.01) && strcmp(block_type->name, "grass") == 0) {
        // create_tree({x, height, z}, this);
      }
    }
  }
}
