#ifndef CAMERA_H
#define CAMERA_H

#include "window.hpp"
#include <memory>

struct Camera {
  int width, height;

  std::unique_ptr<Window> window;

  glm::vec3 position = glm::vec3(0, 90, 0);
  glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 down = glm::vec3(0.0f, -1.0f, 0.0f);
  glm::vec3 right = glm::vec3(0);
  glm::vec3 direction = glm::vec3(0);
  glm::mat4 projection;
  glm::vec3 horizontalFront;
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view;

  glm::vec3 forwardDirection;

  float sensitivity = 0.1f;
  float lastX, lastY;
  float yaw = -90.0f;
  float pitch;

  Camera() = default;
  Camera(int width, int height);

  void mouseCallback(GLFWwindow *window, double xpos, double ypos);
  void lookAt(double xpos, double ypos);
  void update() {
    view = glm::lookAt(position, position + front, up);
  }
};

#endif
