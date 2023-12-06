#include "world_generator.hpp"
#include "../utils/math.hpp"
#include "blocks/wood.hpp"
#include "chunk.hpp"

void WorldGenerator::generateChunk(Chunk *chunk) {
  srand(seed);
  Block *block = new Sand();

  for (int x = 0; x < CHUNK_SIZE; x++) {
    int nX = (x + 1) + chunk->position.x * CHUNK_SIZE;

    for (int z = 0; z < CHUNK_SIZE; z++) {
      int nZ = (z + 1) + chunk->position.z * CHUNK_SIZE;

      const float roughness1 = 0.008;
      const float roughness2 = 0.01;
      const double octave1 =
          perlin.octave2D_01(nX * roughness1, nZ * roughness1, 2);
      const double octave2 =
          perlin.octave2D_01(nX * roughness2, nZ * roughness2, 8);

      int height =
          glm::max(1, (int)((octave1 + octave2) * MAX_WORLD_HEIGHT / 3));

      block = new Grass();
      if (height < WATER_LEVEL + 2) {
        block = new Sand();
      } else if (height < SNOW_LEVEL) {
        block = new Grass();
      } else {
        block = new Snow();
      }

      for (int y = 0; y < height; y++) {
        glm::ivec3 position = {x, y, z};
        chunk->set(glm::ivec3(x, y, z), block);
      }

      for (int y = height; y < WATER_LEVEL; y++) {
        glm::ivec3 position(x, y, z);
        if (y == height)
          chunk->set(position, new Sand());
        else
          chunk->set(position, new Water());
      }

      if (height <= WATER_LEVEL)
        continue;

      glm::ivec3 position(x, height, z);
      if (CHANCE(0.04) && strcmp(block->name, "sand") == 0) {
        createCactus(chunk, position);
      }

      if (CHANCE(0.02) && strcmp(block->name, "grass") == 0) {
        createTree(chunk, position, TreeType::NORMAL);
      }
    }
  }
}

void WorldGenerator::createTree(Chunk *chunk, glm::ivec3 position,
                                TreeType treeType) {
  int treeHeight = RAND(5, 7);
  for (int y = position.y; y < position.y + treeHeight; y++) {
    chunk->set(glm::ivec3(position.x, y, position.z), new Wood(treeType));
  }

  int leavesHeight = RAND(2, 3);
  for (int y = 0; y < leavesHeight; y++) {
    int maxX = leavesHeight - y - 1;
    for (int x = -maxX; x <= maxX; x++) {
      for (int z = -maxX; z <= maxX; z++) {
        chunk->set(position + glm::ivec3(x, y + treeHeight, z), new Leaves());
      }
    }
  }
}

void WorldGenerator::createCactus(Chunk *chunk, glm::ivec3 position) {
  for (int cY = 0; cY < RAND(3, 5); cY++) {
    chunk->set(position + glm::ivec3(0, cY, 0), new Cactus());
  }
}
