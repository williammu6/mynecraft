#include "player.hpp"
#include "GLFW/glfw3.h"

void Player::keyboardCallback(float deltaTime) {
  if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    exit(0);

  float playerSpeed = _speed * deltaTime;
  if (glfwGetKey(_window, GLFW_KEY_F) == GLFW_PRESS)
    state.wireframeMode = !state.wireframeMode;
  if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
    _camera->position += _speed * _camera->front;
  if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
    _camera->position -= _speed * _camera->front;
  if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
    _camera->position -=
        glm::normalize(glm::cross(_camera->front, _camera->up)) * _speed;
  if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
    _camera->position +=
        glm::normalize(glm::cross(_camera->front, _camera->up)) * _speed;
  if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    _camera->position -= glm::vec3(0, 1, 0) * _speed;
  if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
    _camera->position += glm::vec3(0, 1, 0) * _speed;
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
  _ray->setOrigin(state.camera.position);
  _ray->setDirection(state.camera.direction);
  blockIntersection = _ray->intersection(*state.world, _reach);

  if (state.pressed[GLFW_MOUSE_BUTTON_RIGHT]) {
    state.pressed[GLFW_MOUSE_BUTTON_RIGHT] = false;
    if (blockIntersection.has_value()) {
      Intersection intersection = blockIntersection.value();
      Chunk *chunk = state.world->globalPositionToChunk(intersection.position);
      chunk->blocks.erase(intersection.blockPosition);
      state.world->chunksNeedUpdate.push_back(chunk);
    }
  }

  if (state.pressed[GLFW_MOUSE_BUTTON_LEFT]) {
    state.pressed[GLFW_MOUSE_BUTTON_LEFT] = false;
    if (blockIntersection.has_value()) {
      Intersection intersection = blockIntersection.value();
      intersection.placeBlockChunk->set(intersection.placeBlockPosition,
                                        new Cobblestone());
      state.world->chunksNeedUpdate.push_back(intersection.placeBlockChunk);
    }
  }
}
