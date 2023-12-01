#include "player.hpp"
#include "GLFW/glfw3.h"
#include "glm/fwd.hpp"
#include "scene/blocks/glass.hpp"
#include "utils/debug.hpp"

void Player::keyboardCallback(float deltaTime) {
  handleActionKey(GLFW_KEY_F,
                  []() { state.wireframeMode = !state.wireframeMode; });
  handleActionKey(GLFW_KEY_ESCAPE, []() { exit(0); });
  handleMovementKey(GLFW_KEY_W, camera->horizontalFront);
  handleMovementKey(GLFW_KEY_S, camera->horizontalFront * -1.0f);
  handleMovementKey(GLFW_KEY_A, camera->right * -1.0f);
  handleMovementKey(GLFW_KEY_D, camera->right);
  handleMovementKey(GLFW_KEY_LEFT_SHIFT, glm::vec3(0, -1, 0));

  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    if (canJump) {
      state.pressed[GLFW_KEY_SPACE] = true;
      jumping = true;
      jumpStart = state.camera.position;
      canJump = false;
    }
  } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
    state.pressed[GLFW_KEY_SPACE] = false;
  }
}

void Player::handleActionKey(int key, const std::function<void()> &action) {
  if (glfwGetKey(window, key) == GLFW_PRESS) {
    action();
  }
}

void Player::handleMovementKey(int key, glm::vec3 movement) {
  if (glfwGetKey(window, key) == GLFW_PRESS) {
    move(movement * speed * state.deltaTime);
  }
}

void Player::mouseClickCallback(GLFWwindow *_window, int button, int action,
                                int mods) {
  if (action == GLFW_PRESS) {
    state.pressed[button] = true;
  } else if (action == GLFW_RELEASE) {
    state.pressed[button] = false;
  }
}

void Player::mousePosCallback(GLFWwindow *_window, double xpos, double ypos) {
  state.camera.lookAt(xpos, ypos);
}

bool collisionCheck(const glm::vec3 &position) {
  auto maybeBlock = state.world->globalPositionToBlock(position);
  return maybeBlock.has_value();
}

void Player::tick() {
  lookIntersection = ray::cast(state.camera.position, state.camera.direction,
                               collisionCheck, reach);

  if (jumping) {
    const bool midJump =
        glm::length(state.camera.position.y - jumpStart.y) <= jumpHeight;
    if (!(midJump && move(state.camera.up * speed * state.deltaTime * 1.2f))) {
      jumping = false;
    }
  } else {
    canJump = !applyGravity();
  }

  if (state.pressed[GLFW_KEY_SPACE]) {
    state.pressed[GLFW_KEY_SPACE] = false;
    jumping = true;
    jumpStart = state.camera.position;
  } else if (state.pressed[GLFW_MOUSE_BUTTON_LEFT]) {
    state.pressed[GLFW_MOUSE_BUTTON_LEFT] = false;
    tryToDestroyBlock(lookIntersection);
  } else if (state.pressed[GLFW_MOUSE_BUTTON_RIGHT]) {
    state.pressed[GLFW_MOUSE_BUTTON_RIGHT] = false;
    tryToPlaceBlock(lookIntersection);
  }
}

void Player::tryToPlaceBlock(std::optional<ray::Intersection> intersection) {
  if (!intersection)
    return;

  state.world->placeBlockAt(intersection->position, intersection->faceSide,
                            new Glass());
}

void Player::tryToDestroyBlock(std::optional<ray::Intersection> intersection) {
  if (!intersection)
    return;

  state.world->deleteBlockAt(intersection->position);
}

bool Player::canMove(glm::vec3 movement) {
  float playerSpeed = speed * state.deltaTime;
  for (const auto point : boundingBox) {
    auto intersection = ray::cast(state.camera.position + point + movement,
                                  movement, collisionCheck, playerSpeed);
    if (!intersection)
      continue;

    auto maybeBlock =
        state.world->globalPositionToBlock(intersection->position);
    if (maybeBlock.has_value() && !maybeBlock.value()->liquid) {
      return false;
    }
  }

  return true;
}

bool Player::applyGravity() {
  auto movement = camera->down * gravity * state.deltaTime;
  if (canMove(movement)) {
    return move(movement);
  }
  return false;
}

bool Player::move(glm::vec3 movement) {
  if (canMove(movement)) {
    camera->position += movement;
    return true;
  }
  return false;
}
