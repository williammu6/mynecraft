#include "camera.hpp"

Camera::Camera(int width, int height) {
  this->width = width;
  this->height = height;
  lastX = (float)this->width / 2, lastY = (float)this->height / 2;

  direction.x = cos(glm::radians(yaw));
  direction.z = sin(glm::radians(yaw));

  glm::ortho(0.0f, (float)width, 0.0f, (float)height);
  projection = glm::mat4(1.0f);
  view = glm::mat4(1.0f);

  projection = glm::perspective(glm::radians(50.0f),
                                (float)width / (float)height, 0.1f, 400.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::look_at(double xpos, double ypos) {
  float xoffset = xpos - this->lastX;
  float yoffset = this->lastY - ypos;
  this->lastX = xpos;
  this->lastY = ypos;

  xoffset *= sensitivity;
  yoffset *= sensitivity;

  this->yaw += xoffset;
  this->pitch += yoffset;

  if (this->pitch > 89.0f)
    this->pitch = 89.0f;
  if (this->pitch < -89.0f)
    this->pitch = -89.0f;

  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  this->cameraFront = glm::normalize(direction);
}
