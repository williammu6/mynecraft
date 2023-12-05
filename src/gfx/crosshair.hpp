#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include "Mesh/mesh.hpp"
#include "Mesh/vertex.hpp"
#include "shader.hpp"
#include "texture.hpp"

class Crosshair {
  using VertexType = PlainTextureVertex;

public:
  glm::vec3 position;
  std::unique_ptr<Mesh<VertexType>> mesh;

  Crosshair(float windowWidth, float windowHeight) {
    position = glm::vec3(windowWidth / 2.0f, windowHeight / 2.0f, 0);
    shader = new CrosshairShader();
    texture = textureFromPath("assets/textures/crosshair.png");
  }

  void prepare() {
    VertexType v1 = {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)};
    VertexType v2 = {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)};
    VertexType v3 = {glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f)};
    VertexType v4 = {glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f)};

    std::vector<VertexType> vertices = {v1, v2, v3, v4};
    std::vector<unsigned int> indices{0, 1, 3, 1, 2, 3};

    mesh = std::make_unique<Mesh<VertexType>>(vertices, indices,
                                              RenderType::NORMAL);
    mesh->addVertexBuffer({positionAttrib, uvAttrib});
  };

  void render() {
    mesh->draw(position, shader, texture);
  };

private:
  Shader *shader;
  Texture texture;
};

#endif
