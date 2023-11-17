#include "gfx.hpp"
#include "primitive.hpp"
#include "shader.hpp"
#include "texture.hpp"

class Crosshair {
  using VertexType = PlainTextureVertex;

public:
  glm::vec3 position;
  std::unique_ptr<Primitive<VertexType>> primitive;

  Crosshair(float windowWidth, float windowHeight) {
    position = glm::vec3(windowWidth / 2.0f, windowHeight / 2.0f, 0);
  }

  void prepare() {
    VertexType v1 = {.Position = glm::vec3(-0.5f, -0.5f, 0.0f),
                     .uv = glm::vec2(0.0f, 0.0f)};

    VertexType v2 = {.Position = glm::vec3(0.5f, -0.5f, 0.0f),
                     .uv = glm::vec2(1.0f, 0.0f)};

    VertexType v3 = {.Position = glm::vec3(0.5f, 0.5f, 0.0f),
                     .uv = glm::vec2(1.0f, 1.0f)};

    VertexType v4 = {.Position = glm::vec3(-0.5f, 0.5f, 0.0f),
                     .uv = glm::vec2(0.0f, 1.0f)};

    std::vector<VertexType> vertices = {v1, v2, v3, v4};

    std::vector<unsigned int> indices{0, 1, 3, 1, 2, 3};

    primitive = std::make_unique<Primitive<VertexType>>();
    primitive->push(vertices, indices, RenderType::NORMAL);
    primitive->prepare();
  };

  void render() {
    primitive->draw(position, state.renderer->shaders[Shaders::CROSSHAIR],
                    state.renderer->textures[TextureID::CROSSHAIR]);
  }
};
