#ifndef PLAYER_H
#define PLAYER_H

#include "./gfx/primitive.hpp"
#include "gfx/camera.hpp"
#include "state.hpp"
#include "utils/debug.hpp"
#include "utils/ray.hpp"

class Player {
public:
  Player(GLFWwindow *window, struct Camera *camera)
      : _window(window), _camera(camera) {

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetMouseButtonCallback(window, mouseClickCallback);
    glfwSetCursorPosCallback(window, mousePosCallback);
    _ray = std::make_unique<Ray>();
  };
  ~Player(){};

  std::optional<Intersection> blockIntersection;
  void tick();
  void keyboardCallback(float deltaTime);
  static void mousePosCallback(GLFWwindow *window, double xpos, double ypos);
  static void mouseClickCallback(GLFWwindow *window, int button, int action,
                                 int mods);

private:
  float _speed = 0.125f;
  float _reach = 7.5f;
  GLFWwindow *_window;
  struct Camera *_camera;
  std::unique_ptr<Ray> _ray;
};

#endif
