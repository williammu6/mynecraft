#ifndef TREE_H
#define TREE_H

#include "blocks/wood.hpp"
#include "chunk.hpp"

void create_tree(struct Chunk *chunk, glm::ivec3 position, TreeType tree_type);

#endif
