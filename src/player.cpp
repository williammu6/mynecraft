#include "player.hpp"
#include "GLFW/glfw3.h"
#include "glm/fwd.hpp"
#include "utils/debug.hpp"

void Player::keyboardCallback(float deltaTime) {
  if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    exit(0);

  if (glfwGetKey(_window, GLFW_KEY_F) == GLFW_PRESS)
    state.wireframeMode = !state.wireframeMode;
  if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
    move(_camera->horizontalFront * _speed);
  if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
    move(_camera->horizontalFront * _speed * -1.0f);
  if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
    move(_camera->right * _speed);
  if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
    move(_camera->right * _speed * -1.0f);

  if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    move(glm::vec3(0, -1, 0) * _speed);
  if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    move(_camera->up * _speed);
    grounded = false;
  }
}

void Player::mousePosCallback(GLFWwindow *_window, double xpos, double ypos) {
  state.camera.lookAt(xpos, ypos);
}

void Player::mouseClickCallback(GLFWwindow *_window, int button, int action,
                                int mods) {
  if (action == GLFW_PRESS) {
    state.pressed[button] = true;
  } else if (action == GLFW_RELEASE) {
    state.pressed[button] = false;
  }
}

void Player::tick() {
  Ray ray{.origin = state.camera.position, .direction = state.camera.direction};
  blockIntersection = ray.intersection(*state.world, _reach);

  /*
  if (canMove(_camera->down * 0.10f)) {
    move(-_camera->down * 0.10f);
  }
  */

  // DEBUG_VEC3(position);
  if (state.pressed[GLFW_MOUSE_BUTTON_LEFT]) {
    // Delete the block
    state.pressed[GLFW_MOUSE_BUTTON_LEFT] = false;
    if (blockIntersection.has_value()) {
      Intersection intersection = blockIntersection.value();
      auto maybeChunk =
          state.world->globalPositionToChunk(intersection.position + 0.5f);
      if (maybeChunk.has_value()) {
        Chunk *chunk = maybeChunk.value();
        DEBUG_IVEC3(intersection.blockPosition);
        maybeChunk.value()->blocks.erase(intersection.blockPosition);
        state.world->chunksNeedUpdate.push_back(maybeChunk.value());
      }
    }
  }

  if (state.pressed[GLFW_MOUSE_BUTTON_RIGHT]) {
    state.pressed[GLFW_MOUSE_BUTTON_RIGHT] = false;
    if (blockIntersection.has_value()) {
      Intersection intersection = blockIntersection.value();
      if (intersection.placeBlockChunk.has_value()) {
        intersection.placeBlockChunk.value()->set(
            intersection.placeBlockPosition, new Cobblestone());

        state.world->chunksNeedUpdate.push_back(
            intersection.placeBlockChunk.value());
      }
    }
  }
}

void Player::move(glm::vec3 movement) {
  if (canMove(movement)) {
    _camera->position += movement;
  }
}

bool Player::canMove(glm::vec3 movement) {
  for (const auto point : boundingBox) {
    Ray ray{.origin = state.camera.position + point,
            .direction = movement * _speed};

    auto blockIntersection = ray.intersection(*state.world, 0.3f);

    if (!blockIntersection.has_value())
      continue;

    auto maybeBlock = state.world->globalPositionToBlock(
        blockIntersection.value().blockPosition);
    if (maybeBlock.has_value()) {
      // DEBUG_IVEC3(blockPos.value());
      return !aabb.intersects(Block::aabb);
    }
  };

  return true;
}
