#include "tree.hpp"

void create_tree(struct Chunk *chunk, glm::ivec3 position) {
  int tree_height = RAND(5, 7);
  for (int y = position.y; y < position.y + tree_height; y++) {
    glm::ivec3 block_position = {position.x, y, position.z};
    chunk->set(block_position, {new Wood()});
  }

  int leaves_height = RAND(2, 3);
  for (int y = 0; y < leaves_height; y++) {
    int max_x = leaves_height - y - 1;
    for (int x = -max_x; x <= max_x; x++) {
      for (int z = -max_x; z <= max_x; z++) {
        glm::ivec3 p = {x + position.x, y + position.y + tree_height,
                        z + position.z};
        chunk->set(p, {new Leaves()});
      }
    }
  }
  /*

  chunk->set({-1, 20 + tree_height, 0}, {new Leaves()});
  chunk->set({-2, 20 + tree_height, 0}, {new Leaves()});
  chunk->set({-3, 20 + tree_height, 0}, {new Leaves()});
  chunk->set({0, 20 + tree_height, -1}, {new Leaves()});
  chunk->set({0, 20 + tree_height, -2}, {new Leaves()});
  chunk->set({0, 20 + tree_height, -3}, {new Leaves()});
  */
}
