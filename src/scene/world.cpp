#include "world.hpp"
#include "../state.hpp"
#include "blocks/blocks.hpp"
#include "chunk.hpp"
#include "world_utils.hpp"

void World::tick() {
  loadAndUnloadChunks();
  prepareNewChunks(1);
  render();
  deleteFarChunks();
}

bool World::isChunkFar(glm::ivec3 chunkPosition) {
  auto currentChunk = state.getCurrentChunkPosition();
  auto distance = glm::distance(static_cast<glm::vec3>(currentChunk),
                                static_cast<glm::vec3>(chunkPosition));
  return distance > chunkDistance;
}

void World::deleteFarChunks() {
  auto it = chunks.begin();
  while (it != chunks.end()) {
    if (isChunkFar(it->first)) {
      delete it->second;
      it = chunks.erase(it);
    } else {
      ++it;
    }
  }
}

/**
 * sorting chunks is so that water transparency look correct
 * renders chunks from back to front
 */
void World::render() {
  std::vector<glm::ivec3> positions;
  for (const auto &[position, _] : chunks)
    positions.push_back(position);

  glm::vec3 cc = state.getCurrentChunkPosition();

  std::sort(positions.begin(),
            positions.end(),
            [&](const glm::ivec3 &positionA, const glm::ivec3 &positionB) {
              return glm::distance(static_cast<glm::vec3>(positionA), cc) >
                     glm::distance(static_cast<glm::vec3>(positionB), cc);
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
void World::prepareNewChunks(unsigned int maxChunkReloads) {
  for (int i = chunksNeedUpdate.size() - 1; i >= 0 && maxChunkReloads-- >= 0;
       --i) {
    auto chunk = chunksNeedUpdate[i];
    chunk->update();
    for (const auto neighborChunk : chunk->neighbors()) {
      neighborChunk->update();
    }
    chunksNeedUpdate.erase(chunksNeedUpdate.begin() + i);
  }
}

void World::loadAndUnloadChunks() {
  auto cc = state.getCurrentChunkPosition();
  glm::ivec3 start(cc.x - chunkDistance / 2, 0, cc.z - chunkDistance / 2);
  glm::ivec3 end(cc.x + chunkDistance / 2, 0, cc.z + chunkDistance / 2);

  for (int x = start.x; x < end.x; x++) {
    for (int z = start.z; z < end.z; z++) {
      auto newChunkPosition = glm::ivec3(x, 0, z);
      if (chunks.find(newChunkPosition) == chunks.end()) {
        newChunkAt(newChunkPosition);
        return;
      }
    }
  }
}

void World::newChunkAt(glm::vec3 chunkPosition) {
  Chunk *newChunk = new Chunk(chunkPosition, this);
  generator->generateChunk(newChunk);
  chunks[chunkPosition] = newChunk;
  chunksNeedUpdate.push_back(newChunk);
}

std::optional<Chunk *> World::getChunkAt(glm::ivec3 position) {
  if (chunks.find(position) != chunks.end()) {
    return chunks.at(position);
  }
  return std::nullopt;
}

std::optional<Block *> World::globalPositionToBlock(glm::vec3 globalPosition) {
  if (auto chunk = getChunkAt(globalPositionToChunkPosition(globalPosition))) {
    glm::ivec3 blockPosition = globalPositionToBlockPosition(globalPosition);
    return chunk.value()->getBlock(blockPosition);
  }
  return std::nullopt;
}

void World::placeBlockAt(glm::vec3 globalPosition,
                         glm::vec3 faceSide,
                         Block *block) {
  auto placeBlockAt = globalPosition + faceSide;
  if (auto maybeChunk =
          getChunkAt(globalPositionToChunkPosition(globalPosition))) {
    auto &chunk = *maybeChunk;
    chunk->set(globalPositionToBlockPosition(placeBlockAt), block);
    chunksNeedUpdate.push_back(chunk);
  }
}

void World::deleteBlockAt(glm::vec3 globalPosition) {
  if (auto maybeChunk =
          getChunkAt(globalPositionToChunkPosition(globalPosition))) {
    auto chunk = *maybeChunk;
    chunk->blocks.erase(globalPositionToBlockPosition(globalPosition));
    chunksNeedUpdate.push_back(chunk);
  }
}
