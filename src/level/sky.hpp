#ifndef SKY_H
#define SKY_H

#include "../common.hpp"
#include "../gfx/gfx.hpp"
#include "../gfx/primitive.hpp"
#include "../state.hpp"

class Sky {
private:
  GLuint VAO, VBO, EBO;
  Shader *sun_shader;
  Primitive *primitive;

public:
  Sky() {
    Shader shader = Shader("res/shaders/sun.vert",
                           "res/shaders/sun.frag");
    primitive = new Primitive();
    this->sun_shader = &shader;
    prepare_render();
  }
  void prepare_render();
  void render();
};

#endif
