#include "world_utils.hpp"

glm::ivec3 globalPositionToChunkPosition(glm::vec3 p) {
  glm::ivec3 chunkPosition = {
      p.x < 0 ? p.x / CHUNK_SIZE - 1 : p.x / CHUNK_SIZE,
      0,
      p.z < 0 ? p.z / CHUNK_SIZE - 1 : p.z / CHUNK_SIZE,
  };

  return chunkPosition;
}

glm::ivec3 globalPositionToBlockPosition(glm::vec3 p) {
  float localX = fmodf(glm::floor(p.x), CHUNK_SIZE);
  float localZ = fmodf(glm::floor(p.z), CHUNK_SIZE);
  localX = fmodf(localX + CHUNK_SIZE, CHUNK_SIZE);
  localZ = fmodf(localZ + CHUNK_SIZE, CHUNK_SIZE);
  return glm::ivec3(localX, glm::floor(p.y), localZ);
}
