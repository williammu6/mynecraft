#ifndef STATE_H
#define STATE_H

#include "gfx/camera.hpp"
#include "gfx/crosshair.hpp"
#include "gfx/renderer.hpp"
#include "gfx/window.hpp"
#include "scene/world.hpp"
#include <memory>
#include <unordered_map>

struct State {
  Camera camera;
  Renderer *renderer;

  bool running = false;
  bool wireframeMode = false;
  float aspectRatio;
  float deltaTime = 0;
  float tick;
  int frames = 0;
  int windowHeight;
  int windowWidth;

  glm::ivec3 currentChunkPosition;
  glm::ivec3 currentBlockPosition;
  glm::ivec3 currentGlobalBlockPosition;

  std::shared_ptr<Window> window;
  std::unordered_map<int, bool> pressed;
  Crosshair *crosshair;
  struct World *world;

  glm::ivec3 getCurrentChunkPosition() {
    auto currentPosition = this->camera.position;

    int currX = currentPosition.x < 0 ? currentPosition.x / CHUNK_SIZE - 1
                                      : currentPosition.x / CHUNK_SIZE;
    int currZ = currentPosition.z < 0 ? currentPosition.z / CHUNK_SIZE - 1
                                      : currentPosition.z / CHUNK_SIZE;
    return glm::ivec3(currX, 0, currZ);
  }

  State() {
    windowWidth = 1800;
    windowHeight = 1200;

    aspectRatio =
        static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

    window = std::make_unique<Window>();
    camera = Camera(windowWidth, windowHeight);
  }
};

extern State &state;

#endif
