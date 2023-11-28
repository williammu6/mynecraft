#ifndef PLAYER_H
#define PLAYER_H

#include "./gfx/cube_face.hpp"
#include "gfx/camera.hpp"
#include "state.hpp"
#include "utils/debug.hpp"
#include "utils/ray.hpp"

class Player {
public:
  Player(GLFWwindow *window, struct Camera *camera)
      : window(window), camera(camera) {

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetMouseButtonCallback(window, mouseClickCallback);
    glfwSetCursorPosCallback(window, mousePosCallback);
  };
  ~Player(){};

  std::optional<ray::Intersection> lookIntersection;
  void tick();
  void keyboardCallback(float deltaTime);
  static void mousePosCallback(GLFWwindow *window, double xpos, double ypos);
  static void mouseClickCallback(GLFWwindow *window, int button, int action,
                                 int mods);

private:
  float speed = 0.035f;
  float reach = 5.0f;
  float gravity = -0.075;
  float jumpHeight = 2.0f;
  bool jumping = false;
  bool canJump = false;
  glm::vec3 jumpStart;

  struct Camera *camera;
  GLFWwindow *window;

  glm::vec3 position;
  std::unordered_map<unsigned int, bool> keyPress;
  std::vector<glm::vec3> boundingBox{
      {-0.3, -1.5, -0.3}, {-0.3, -1.5, 0.3}, {0.3, -1.5, -0.3},
      {0.3, -1.5, 0.3},   {-0.3, 0.3, -0.3}, {-0.3, 0.3, 0.3},
      {0.3, 0.3, -0.3},   {0.3, 0.3, 0.3},
  };

  bool applyGravity();
  bool canMove(glm::vec3 newPosition);
  bool move(glm::vec3 movement);

  void handleActionKey(int key, const std::function<void()> &action);
  void handleMovementKey(int key, glm::vec3 movement);
  void tryToDestroyBlock(std::optional<ray::Intersection> maybeIntersection);
  void tryToPlaceBlock(std::optional<ray::Intersection> maybeIntersection);
};

#endif
