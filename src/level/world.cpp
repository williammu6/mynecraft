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

glm::ivec3 get_current_chunk_position() {
  int currX = state.camera.position.x < 0 ? state.camera.position.x / 16 - 1
                                          : state.camera.position.x / 16;
  int currZ = state.camera.position.z < 0 ? state.camera.position.z / 16 - 1
                                          : state.camera.position.z / 16;
  return glm::ivec3(currX, 0, currZ);
}

Chunk *World::currentChunk() {
  return getChunkAt(get_current_chunk_position());
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
      chunks.erase(it++);
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
              glm::vec3 diff = b - a;
              return glm::dot(diff, diff);
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
void World::prepareNewChunks(unsigned int maxThrottle) {
  for (int i = 0; i < chunksNeedUpdate.size() && maxThrottle-- >= 0; i++) {
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

Block *World::blockAt(glm::vec3 p) {
  glm::vec3 chunkPos = glm::floor(p) / (float)CHUNK_SIZE;
  chunkPos.y = 0;
  Chunk *chunk = getChunkAt(chunkPos);
  if (chunk == nullptr)
    return nullptr;

  glm::ivec3 localBlockPosition = {(int)glm::floor(p.x) % CHUNK_SIZE,
                                   glm::floor(p.y),
                                   (int)glm::floor(p.z) % CHUNK_SIZE};

  if (localBlockPosition.x < 0)
    localBlockPosition.x = CHUNK_SIZE + localBlockPosition.x;
  if (localBlockPosition.z < 0)
    localBlockPosition.z = CHUNK_SIZE + localBlockPosition.z;
  // printf("Local block position %d %d %d\n", localBlockPosition.x, localBlockPosition.y, localBlockPosition.z);

  return chunk->getBlock(localBlockPosition);
}

void World::updateBlockAt(glm::vec3 globalPosition) {
  glm::ivec3 chunkPosition = (glm::ivec3)globalPosition / CHUNK_SIZE;
  chunkPosition.y = 0;
  Chunk *chunk = getChunkAt(chunkPosition);
  if (chunk == nullptr)
    return;

  glm::ivec3 blockPosition = glm::floor(globalPosition);

  blockPosition.x = blockPosition.x % CHUNK_SIZE;
  if (blockPosition.x < 0)
    blockPosition.x += CHUNK_SIZE;
  blockPosition.z = blockPosition.z % CHUNK_SIZE;
  if (blockPosition.z < 0)
    blockPosition.z += CHUNK_SIZE;

  chunk->set(blockPosition, new Water());
  chunk->update();
}
