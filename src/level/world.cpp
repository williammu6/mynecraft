#include "world.hpp"
#include "../utils/math.hpp"
#include "blocks/blocks.hpp"
#include "chunk.hpp"
#include "glm/common.hpp"

void World::tick() {
  loadAndUnloadChunks();
  prepareNewChunks(1);
  render();
  deleteFarChunks();
}

float squaredDistance(const glm::ivec3 &a, const glm::ivec3 &b) {
  glm::vec3 diff = b - a;
  return glm::dot(diff, diff);
}

bool sortByDistance(const glm::ivec3 &a, const glm::ivec3 &b,
                    const glm::ivec3 &reference) {
  return squaredDistance(a, reference) > squaredDistance(b, reference);
}

glm::ivec3 get_current_chunk_position() {
  int currX = state.camera.position.x < 0 ? state.camera.position.x / 16 - 1
                                          : state.camera.position.x / 16;
  int currZ = state.camera.position.z < 0 ? state.camera.position.z / 16 - 1
                                          : state.camera.position.z / 16;
  return glm::ivec3(currX, 0, currZ);
}

bool World::isChunkFar(glm::ivec3 chunkPosition) {
  glm::ivec3 cc = get_current_chunk_position();
  auto diff = chunkPosition - cc;
  return std::abs(diff.x) > nChunks || std::abs(diff.z) > nChunks;
}

void World::deleteFarChunks() {
  auto it = chunks.begin();
  while (it != chunks.end()) {
    if (isChunkFar(it->first)) {
      delete it->second;
      chunks.erase(it);
    }
    it++;
  }
}

/**
 * renders chunks from furthest to closer
 * so water transparency works correclty
 */
void World::render() {
  glm::ivec3 cc = get_current_chunk_position();

  std::vector<glm::ivec3> positions;
  for (const auto &[position, _] : chunks) {
    positions.push_back(position);
  }

  std::sort(positions.begin(), positions.end(),
            [&](const glm::ivec3 &a, const glm::ivec3 &b) {
              return sortByDistance(a, b, cc);
            });

  for (const auto position : positions) {
    chunks[position]->render();
  }
}

/**
 * update chunk mesh (vertices and indices)
 * this happens every time a chunk changes or one of its neighbors change
 * it is important so block faces between chunks aren't rendered
 */
void World::prepareNewChunks(unsigned int max_throttle) {
  for (int i = 0; i < chunksNeedUpdate.size() && max_throttle-- >= 0; i++) {
    Chunk *chunk = chunksNeedUpdate[i];
    chunk->update();
    for (const auto neighborChunk : chunk->neighbors()) {
      neighborChunk->update();
    }
    chunksNeedUpdate.erase(chunksNeedUpdate.begin() + i);
    i--;
  }
}

void World::newChunkAt(glm::ivec3 chunkPosition) {
  Chunk *newChunk = createChunk(chunkPosition, this);
  chunks[chunkPosition] = newChunk;
  chunksNeedUpdate.push_back(newChunk);
  version++;
}

void World::loadAndUnloadChunks() {
  glm::ivec3 cc = get_current_chunk_position();
  for (int x = cc.x - nChunks; x < cc.x + nChunks; x++) {
    for (int z = cc.z - nChunks; z < cc.z + nChunks; z++) {
      auto newChunkPosition = glm::ivec3(x, 0, z);
      if (chunks.find(newChunkPosition) == chunks.end()) {
        newChunkAt(newChunkPosition);
        return;
      }
    }
  }
}

Chunk *World::getChunkAt(glm::ivec3 position) {
  if (chunks.find(position) != chunks.end()) {
    return chunks.at(position);
  }
  return nullptr;
}

void World::putPendingBlocks(Chunk *chunk) {
  for (int i = 0; i < pendingBlocks.size(); i++) {
    PendingBlock pendingBlock = pendingBlocks[i];
    if (pendingBlock.chunkPosition.x == chunk->position.x &&
        pendingBlock.chunkPosition.z == chunk->position.z) {
      chunk->set(pendingBlock.blockPosition, pendingBlock.block);
      pendingBlocks.erase(pendingBlocks.begin() + i);
    }
  }
}
