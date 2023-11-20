#include "camera.hpp"

Camera::Camera(int width, int height) : width(width), height(height) {
  lastX = (float)width / 2, lastY = (float)height / 2;

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

void Camera::lookAt(double xpos, double ypos) {
  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;
  lastX = xpos;
  lastY = ypos;

  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw += xoffset;
  pitch += yoffset;

  if (pitch > 89.0f)
    pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;

  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(direction);
  right = glm::normalize(glm::cross(front, up));
  horizontalFront = glm::normalize(glm::vec3(front.x, 0, front.z));
}

void Camera::mouseCallback(GLFWwindow *window, double xpos, double ypos) {
  printf("%.2f %.2f\n", xpos, ypos);
}
