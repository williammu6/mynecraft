#ifndef PLAYER_H
#define PLAYER_H

#include "gfx/camera.hpp"
#include "glm/fwd.hpp"
#include "scene/blocks/cactus.hpp"
#include "scene/blocks/cobblestone.hpp"
#include "scene/blocks/glass.hpp"
#include "scene/blocks/grass.hpp"
#include "scene/blocks/leaves.hpp"
#include "scene/blocks/sand.hpp"
#include "scene/blocks/stone.hpp"
#include "scene/blocks/wood.hpp"
#include "utils/ray.hpp"
#include <unordered_map>

class Player {
public:
  Player(GLFWwindow *window, struct Camera *camera)
      : camera(camera), window(window) {

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetMouseButtonCallback(window, mouseClickCallback);
    glfwSetCursorPosCallback(window, mousePosCallback);

    inventory = std::vector<std::optional<Block *>>(9, std::nullopt);

    inventory[1] = new Glass();
    inventory[2] = new Grass();
    inventory[3] = new Cobblestone();
    inventory[4] = new Wood(TreeType::NORMAL);
    inventory[5] = new Sand();
    inventory[6] = new Leaves();
    inventory[7] = new Cactus();
  };
  ~Player() {};

  std::optional<ray::Intersection> lookIntersection;
  void tick();
  void keyboardCallback(float deltaTime);
  static void mousePosCallback(GLFWwindow *window, double xpos, double ypos);
  static void
  mouseClickCallback(GLFWwindow *window, int button, int action, int mods);

private:
  float speed = 3.8f;
  float reach = 5.0f;
  float gravity = 7.0f;
  float jumpHeight = 1.7f;
  bool jumping = false;
  bool canJump = false;

  std::vector<std::optional<Block *>> inventory;

  int selectedItemInventoryIdx = 0;
  glm::vec3 movement;
  glm::vec3 jumpStart;

  struct Camera *camera;
  GLFWwindow *window;

  glm::vec3 position;
  std::unordered_map<unsigned int, bool> keyPress;
  std::vector<glm::vec3> boundingBox{
      {-0.3, -1.5, -0.3},
      {-0.3, -1.5, 0.3},
      {0.3, -1.5, -0.3},
      {0.3, -1.5, 0.3},

      {-0.3, -0.5f, -0.3},
      {-0.3, -0.5f, 0.3},
      {0.3, -0.5f, -0.3},
      {0.3, -0.5f, 0.3},

      {-0.3, 0.3, -0.3},
      {-0.3, 0.3, 0.3},
      {0.3, 0.3, -0.3},
      {0.3, 0.3, 0.3},
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
