#include "tree.hpp"
#include "blocks/wood.hpp"

void create_tree(struct Chunk *chunk, glm::ivec3 position, TreeType tree_type) {
  int tree_height = RAND(5, 7);
  for (int y = position.y; y < position.y + tree_height; y++) {
    glm::ivec3 block_position = {position.x, y, position.z};
    chunk->set(block_position, new Wood(tree_type));
  }

  int leaves_height = RAND(2, 3);
  for (int y = 0; y < leaves_height; y++) {
    int max_x = leaves_height - y - 1;
    for (int x = -max_x; x <= max_x; x++) {
      for (int z = -max_x; z <= max_x; z++) {
        glm::ivec3 p = {x + position.x, y + position.y + tree_height,
                        z + position.z};
        chunk->set(p, new Leaves());
      }
    }
  }
}
