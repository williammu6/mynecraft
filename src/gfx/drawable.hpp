#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Mesh/mesh.hpp"
#include "shader.hpp"
#include "texture.hpp"

template <typename T> class Drawable {
public:
  Drawable();
  void render() {
    mesh->draw(position, shader, texture);
  }
  virtual void prepare() = 0;

private:
  glm::vec3 position;
  std::unique_ptr<Mesh<T>> mesh;
  Shader *shader;
  Texture texture;
};

#endif
