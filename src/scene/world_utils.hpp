#ifndef WORLD_UTILS_H
#define WORLD_UTILS_H

#include "glm/glm.hpp"
#include "chunk.hpp"
#include "../state.hpp"

glm::ivec3 globalPositionToChunkPosition(glm::vec3 globalPosition);
glm::ivec3 globalPositionToGlobalBlockPosition(glm::vec3 globalPosition);
glm::ivec3 globalPositionToBlockPosition(glm::vec3 globalPosition);
glm::ivec3 getCurrentChunkPosition(glm::vec3 currentPosition);

#endif
