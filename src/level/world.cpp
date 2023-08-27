#include "world.hpp" 
#include "../utils/math.hpp"
#include "blocks/blocks.hpp"
#include "glm/common.hpp"

void World::init()
{
  for (int x = 0; x < n_chunks; x++)
  {
    for (int z = 0; z < n_chunks; z++)
    {
      this->chunk_map[{x, 0, z}] = create_chunk(glm::vec3(x, 0, z), this);
    }
  }

  for (const auto &[position, chunk] : chunk_map)
  {
    put_blocks_outta_bounds(chunk);
    chunk->update();
  }

  glm::vec3 center =
      (glm::vec3)chunk_map[{n_chunks - 1, 0, n_chunks - 1}]->position * 16.0f *
      0.5f;
  state.camera.position = glm::vec3(center.x, 40, center.z);
}

void World::render()
{
  bool new_chunks = false;
  std::vector<Chunk *> new_chunks_vec{};

  auto it = chunk_map.begin();

  while (it != chunk_map.end())
  {
    Chunk *chunk = it->second;
    auto xyChunk = glm::vec3(chunk->position.x, 0, chunk->position.z);
    auto xyCamera =
        glm::vec3(state.camera.position.x, 0, state.camera.position.z);

    float distance = (float)n_chunks * chunk->SIZE / 2;
    float tooFar = distance * 4;

    float distanceX =
        chunk->position.x * (float)chunk->SIZE - state.camera.position.x;
    float distanceZ =
        chunk->position.z * (float)chunk->SIZE - state.camera.position.z;

    if (distanceX <= distance && distanceX >= -distance &&
        distanceZ <= distance && distanceZ >= -distance)
    {
      it++;
      continue;
    }

    int newX = it->first.x;
    int newZ = it->first.z;

    if (distanceX > distance)
      newX -= n_chunks;
    if (distanceX < -distance)
      newX += n_chunks;
    if (distanceZ > distance)
      newZ -= n_chunks;
    if (distanceZ < -distance)
      newZ += n_chunks;

    if (newX != chunk->position.x || newZ != chunk->position.z)
    {
      new_chunks = true;
      glm::vec3 new_chunk_position = glm::vec3(newX, 0, newZ);
      delete chunk;
      chunk_map.erase(it++);
      Chunk *new_chunk = create_chunk(new_chunk_position, this);
      chunk_map[{newX, 0, newZ}] = new_chunk;
      new_chunks_vec.push_back(new_chunk);
      put_blocks_outta_bounds(new_chunk);
    }
    else
    {
      it++;
    }
  }

  if (new_chunks)
  {
    this->version++;
    for (Chunk *chunk : new_chunks_vec)
    {
      chunk->update();
      for (Chunk *neighbor : chunk->neighbors())
      {
        if (neighbor->version != this->version)
        {
          neighbor->update();
        }
      }
    }
  }

  for (const auto &[position, chunk] : chunk_map) {
    chunk->render();
  }

}

Chunk *World::get_chunk_at(int x, int z)
{
  if (chunk_map.find({x, 0, z}) != chunk_map.end())
  {
    return chunk_map.at({x, 0, z});
  }
  return nullptr;
}

void World::put_blocks_outta_bounds(Chunk *chunk)
{
  for (int i = 0; i < out_bounds_blocks.size(); i++)
  {
    OutOfBoundsBlock outtabounds = out_bounds_blocks[i];
    if (outtabounds.chunk_position.x == chunk->position.x &&
        outtabounds.chunk_position.z == chunk->position.z)
    {
      chunk->set(outtabounds.block_position, outtabounds.block);
      out_bounds_blocks.erase(out_bounds_blocks.begin() + i);
    }
  }
}
