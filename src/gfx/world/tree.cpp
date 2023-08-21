#include "tree.hpp"

void create_tree(glm::vec3 root_position, Chunk *chunk) {
  int tree_height = 5;
  int tree_top = root_position.y + tree_height;

  for (int y = root_position.y; y < tree_top; y++) {
    glm::vec3 position = {root_position.x, y, root_position.z};
    chunk->set(position, {new Wood(), position});
  }
  for (int xx = root_position.x - 3; xx < root_position.x + 3; xx++) {
    for (int zz = root_position.z - 3; zz < root_position.z + 3; zz++) {
      for (int yy = tree_top; yy < tree_top + 3; yy++) {
        glm::vec3 position = {xx, yy, zz};
        chunk->set(position, {new Leaves(), position});
      }
    }
  }
}
