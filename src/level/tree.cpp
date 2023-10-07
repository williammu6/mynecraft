#include "tree.hpp"
#include "blocks/wood.hpp"

void createTree(struct Chunk *chunk, glm::ivec3 position, TreeType treeType) {
  int treeHeight = RAND(5, 7);
  for (int y = position.y; y < position.y + treeHeight; y++) {
    glm::ivec3 block_position = {position.x, y, position.z};
    chunk->set(block_position, new Wood(treeType));
  }

  int leavesHeight = RAND(2, 3);
  for (int y = 0; y < leavesHeight; y++) {
    int maxX = leavesHeight - y - 1;
    for (int x = -maxX; x <= maxX; x++) {
      for (int z = -maxX; z <= maxX; z++) {
        glm::ivec3 p = {x + position.x, y + position.y + treeHeight,
                        z + position.z};
        chunk->set(p, new Leaves());
      }
    }
  }
}
