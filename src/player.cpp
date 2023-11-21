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
    move(_camera->horizontalFront * speed);
  if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
    move(_camera->horizontalFront * speed * -1.0f);
  if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
    move(_camera->right * speed);
  if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
    move(_camera->right * speed * -1.0f);

  if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    move(glm::vec3(0, -1, 0) * speed);
  if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
    move(_camera->up + glm::vec3(0, 1, 0) * speed);
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

bool colisionCheck(glm::vec3 position) {
  auto maybeBlock = state.world->globalPositionToBlock(position);
  return maybeBlock.has_value();
  ;
}

void Player::tick() {
  Ray ray{.origin = state.camera.position, .direction = state.camera.direction};
  lookIntersection = ray.intersection(colisionCheck, reach);

  applyGravity();

  if (state.pressed[GLFW_MOUSE_BUTTON_LEFT]) {
    state.pressed[GLFW_MOUSE_BUTTON_LEFT] = false;
    tryToDestroyBlock(lookIntersection);
  }

  if (state.pressed[GLFW_MOUSE_BUTTON_RIGHT]) {
    state.pressed[GLFW_MOUSE_BUTTON_RIGHT] = false;
    tryToPlaceBlock(lookIntersection);
  }
}

void Player::tryToPlaceBlock(std::optional<Intersection> maybeIntersection) {
  if (!maybeIntersection.has_value())
    return;

  auto intersection = maybeIntersection.value();

  auto maybeChunk = state.world->globalPositionToChunk(intersection.position);
  auto placePosition =
      state.world->globalPositionToChunk(intersection.position);
  if (maybeChunk.has_value()) {
    maybeChunk.value()->set(state.world->globalPositionToBlockPosition(
                                intersection.position + intersection.faceSide),
                            new Cobblestone());
    state.world->chunksNeedUpdate.push_back(maybeChunk.value());
  }
}

void Player::tryToDestroyBlock(std::optional<Intersection> intersection) {
  if (!intersection.has_value())
    return;
  auto intersectionPosition = intersection.value().position;

  auto maybeChunk = state.world->globalPositionToChunk(intersectionPosition);

  if (maybeChunk.has_value()) {
    auto chunk = maybeChunk.value();
    maybeChunk.value()->blocks.erase(
        state.world->globalPositionToBlockPosition(intersectionPosition));
    state.world->chunksNeedUpdate.push_back(maybeChunk.value());
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
            .direction = movement * speed};

    auto intersection = ray.intersection(colisionCheck, 0.3f);

    if (!intersection.has_value())
      continue;

    if (state.world->globalPositionToBlock(intersection.value().position)) {
      return !aabb.intersects(Block::aabb);
    }
  };

  return true;
}

void Player::applyGravity() {
  if (canMove(_camera->up * gravity)) {
    move(_camera->up * gravity);
  }
}
