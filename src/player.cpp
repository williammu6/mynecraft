#include "player.hpp"
#include "GLFW/glfw3.h"
#include "glm/fwd.hpp"
#include "utils/debug.hpp"

void Player::keyboardCallback(float deltaTime) {
  handleActionKey(GLFW_KEY_F,
                  []() { state.wireframeMode = !state.wireframeMode; });
  handleActionKey(GLFW_KEY_ESCAPE, []() { exit(0); });
  handleMovementKey(GLFW_KEY_W, camera->horizontalFront);
  handleMovementKey(GLFW_KEY_S, camera->horizontalFront * -1.0f);
  handleMovementKey(GLFW_KEY_A, camera->right * -1.0f);
  handleMovementKey(GLFW_KEY_D, camera->right);
  handleMovementKey(GLFW_KEY_SPACE, camera->up + glm::vec3(0, 0.5, 0));
  handleMovementKey(GLFW_KEY_LEFT_SHIFT, glm::vec3(0, -1, 0));
}

void Player::handleActionKey(int key, const std::function<void()> &action) {
  if (glfwGetKey(window, key) == GLFW_PRESS) {
    action();
  }
}

void Player::handleMovementKey(int key, glm::vec3 movement) {
  if (glfwGetKey(window, key) == GLFW_PRESS) {
    move(movement * speed);
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

bool colisionCheck(glm::vec3 position) {
  auto maybeBlock = state.world->globalPositionToBlock(position);
  return maybeBlock.has_value();
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

void Player::tryToPlaceBlock(std::optional<Intersection> intersection) {
  if (!intersection)
    return;

  state.world->placeBlockAt(intersection->position, intersection->faceSide,
                            new Sand());
}

void Player::tryToDestroyBlock(std::optional<Intersection> intersection) {
  if (!intersection)
    return;
  state.world->deleteBlockAt(intersection->position);
}

void Player::move(glm::vec3 movement) {
  if (canMove(movement)) {
    camera->position += movement;
  }
}

bool Player::canMove(glm::vec3 movement) {
  for (const auto point : boundingBox) {
    Ray ray{.origin = state.camera.position + point, .direction = movement};

    if (auto intersection = ray.intersection(colisionCheck, speed)) {
      if (state.world->globalPositionToBlock(intersection->position)) {
        if (Player::aabb.intersects(Block::aabb)) {
          return false;
        }
      }
    }
  };

  return true;
}

void Player::applyGravity() {
  if (canMove(camera->up * gravity)) {
    move(camera->up * gravity);
  }
}
