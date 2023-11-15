#ifndef CAMERA_H
#define CAMERA_H

#include "../common.hpp"
#include "gfx.hpp"
#include "window.hpp"

struct Camera {
  int width, height;

  std::unique_ptr<Window> window;

  glm::vec3 position = glm::vec3(0, 100, 0);
  glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 direction;
  glm::mat4 projection;
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view;

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
