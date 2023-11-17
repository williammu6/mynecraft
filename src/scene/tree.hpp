#ifndef TREE_H
#define TREE_H

#include "blocks/wood.hpp"
#include "chunk.hpp"

void createTree(struct Chunk *chunk, glm::ivec3 position, TreeType treeType);

#endif
