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
  int currX = state.camera.position.x < 0
                  ? state.camera.position.x / CHUNK_SIZE - 1
                  : state.camera.position.x / CHUNK_SIZE;
  int currZ = state.camera.position.z < 0
                  ? state.camera.position.z / CHUNK_SIZE - 1
                  : state.camera.position.z / CHUNK_SIZE;
  return glm::ivec3(currX, 0, currZ);
}

bool World::isChunkFar(glm::ivec3 chunkPosition) {
  glm::ivec3 cc = get_current_chunk_position();
  auto diff = chunkPosition - cc;
  return std::abs(diff.x) > chunkDistance || std::abs(diff.z) > chunkDistance;
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
 * renders chunks from furthest to closer
 * so water transparency works correclty
 */
void World::render() {
  std::vector<glm::ivec3> positions;
  for (const auto &[position, _] : chunks)
    positions.push_back(position);

  std::sort(positions.begin(), positions.end(),
            [&](const glm::ivec3 &a, const glm::ivec3 &b) {
              float d1 = glm::distance((glm::vec3)a, state.camera.position);
              float d2 = glm::distance((glm::vec3)b, state.camera.position);
              return d1 > d2;
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
  for (int i = 0; i < chunksNeedUpdate.size() && maxChunkReloads-- >= 0; i++) {
    auto chunk = chunksNeedUpdate[i];
    chunk->update();
    for (const auto neighborChunk : chunk->neighbors()) {
      if (neighborChunk) {
        neighborChunk.value()->update();
      }
    }
    chunksNeedUpdate.erase(chunksNeedUpdate.begin() + i);
    i--;
  }
}

void World::loadAndUnloadChunks() {
  auto cc = get_current_chunk_position();
  for (int x = cc.x - chunkDistance / 2; x < cc.x + chunkDistance / 2; x++) {
    for (int z = cc.z - chunkDistance / 2; z < cc.z + chunkDistance / 2; z++) {
      auto newChunkPosition = glm::ivec3(x, 0, z);
      if (chunks.find(newChunkPosition) == chunks.end()) {
        newChunkAt(newChunkPosition);
        if (chunks.size() >= chunkDistance * chunkDistance)
          return;
      }
    }
  }
}

void World::newChunkAt(glm::ivec3 chunkPosition) {
  Chunk *newChunk = createChunk(chunkPosition, this);
  chunks[chunkPosition] = newChunk;
  chunksNeedUpdate.push_back(newChunk);
  version++;
}

std::optional<Chunk *> World::getChunkAt(glm::ivec3 position) {
  if (chunks.find(position) != chunks.end()) {
    return chunks.at(position);
  }
  return std::nullopt;
}

std::optional<Chunk *> World::globalPositionToChunk(glm::vec3 p) {
  glm::ivec3 chunkPosition = {
      p.x < 0 ? p.x / CHUNK_SIZE - 1 : p.x / CHUNK_SIZE,
      0,
      p.z < 0 ? p.z / CHUNK_SIZE - 1 : p.z / CHUNK_SIZE,
  };
  chunkPosition.y = 0;
  return getChunkAt(chunkPosition);
}

glm::ivec3 World::globalPositionToBlockPosition(glm::vec3 gp) {
  float localX = std::fmodf(glm::floor(gp.x), CHUNK_SIZE);
  float localZ = std::fmodf(glm::floor(gp.z), CHUNK_SIZE);

  localX = fmodf(localX + CHUNK_SIZE, CHUNK_SIZE);
  localZ = fmodf(localZ + CHUNK_SIZE, CHUNK_SIZE);

  return glm::ivec3(localX, glm::floor(gp.y), localZ);
}

std::optional<Block *> World::globalPositionToBlock(glm::vec3 globalPosition) {
  if (auto chunk = globalPositionToChunk(globalPosition)) {
    glm::ivec3 blockPosition = globalPositionToBlockPosition(globalPosition);
    return chunk.value()->getBlock(blockPosition);
  }
  return std::nullopt;
}

void World::placeBlockAt(glm::vec3 globalPosition, glm::vec3 faceSide,
                         Block *block) {
  if (auto maybeChunk = state.world->globalPositionToChunk(globalPosition)) {
    auto &chunk = *maybeChunk;
    chunk->set(globalPositionToBlockPosition(globalPosition + faceSide), block);
    chunksNeedUpdate.push_back(maybeChunk.value());
  }
}

void World::deleteBlockAt(glm::vec3 globalPosition) {
  if (auto maybeChunk = globalPositionToChunk(globalPosition)) {
    auto chunk = *maybeChunk;
    chunk->blocks.erase(globalPositionToBlockPosition(globalPosition));
    state.world->chunksNeedUpdate.push_back(maybeChunk.value());
  }
}
