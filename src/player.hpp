#ifndef PLAYER_H
#define PLAYER_H

#include "./gfx/cube_face.hpp"
#include "gfx/camera.hpp"
#include "physics/aabb.hpp"
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
  };
  ~Player(){};

  std::optional<Intersection> lookIntersection;
  bool canMove(glm::vec3 newPosition);
  void tick();
  void keyboardCallback(float deltaTime);
  static void mousePosCallback(GLFWwindow *window, double xpos, double ypos);
  static void mouseClickCallback(GLFWwindow *window, int button, int action,
                                 int mods);

private:
  float _speed = 0.055f;
  float _reach = 7.5f;
  bool grounded = false;
  struct AABB aabb = {.min = glm::vec3(-0.3f, -1.5f, -0.3f),
                      .max = glm::vec3(0.3, 0.3f, 0.3)};
  GLFWwindow *_window;
  glm::vec3 position;
  std::unordered_map<unsigned int, bool> keyPress;
  struct Camera *_camera;
  void move(glm::vec3 movement);
  std::vector<glm::vec3> boundingBox{
      {-0.3, -1.5, -0.3}, {-0.3, -1.5, 0.3},
      {0.3, -1.5, -0.3},  {0.3, -1.5, 0.3},

      {-0.3, 0.3, -0.3},  {-0.3, 0.3, 0.3},
      {0.3, 0.3, -0.3},   {0.3, 0.3, 0.3},
  };

  void tryToPlaceBlock(std::optional<Intersection> maybeIntersection);
  void tryToDestroyBlock(std::optional<Intersection> maybeIntersection);
};

#endif
