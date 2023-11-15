#include "gfx.hpp"
#include "primitive.hpp"
#include "shader.hpp"
#include "texture.hpp"

class Crosshair {
public:
  glm::vec3 position;
  std::unique_ptr<Primitive> primitive;

  Crosshair(float windowWidth, float windowHeight) {
    position = glm::vec3(windowWidth / 2.0f, windowHeight / 2.0f, 0);
  }

  void prepare() {

    Vertex v1 = {.Position = glm::vec3(-0.5f, -0.5f, 0.0f),
                 .FaceDirection = glm::ivec3(0),
                 .TexCoords = glm::vec2(0.0f, 0.0f)};

    Vertex v2 = {.Position = glm::vec3(0.5f, -0.5f, 0.0f),
                 .FaceDirection = glm::ivec3(0),
                 .TexCoords = glm::vec2(1.0f, 0.0f)};

    Vertex v3 = {.Position = glm::vec3(0.5f, 0.5f, 0.0f),
                 .FaceDirection = glm::ivec3(0),
                 .TexCoords = glm::vec2(1.0f, 1.0f)};

    Vertex v4 = {.Position = glm::vec3(-0.5f, 0.5f, 0.0f),
                 .FaceDirection = glm::ivec3(0),
                 .TexCoords = glm::vec2(0.0f, 1.0f)};

    std::vector<Vertex> vertices = {v1, v2, v3, v4};

    std::vector<unsigned int> indices{0, 1, 3, 1, 2, 3};

    primitive = std::make_unique<Primitive>();
    primitive->push(vertices, indices, RenderType::NORMAL);
    primitive->prepare();
  };

  void render() {
    primitive->draw(position, state.renderer->shaders[Shaders::CROSSHAIR],
                    state.renderer->textures[TextureID::CROSSHAIR]);
  }
};
