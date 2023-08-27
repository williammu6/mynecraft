#ifndef SKY_H
#define SKY_H

#include "../gfx/gfx.hpp"
#include "../state.hpp"

class Sky {
private:
  GLuint VAO, VBO, EBO;
  Shader *sun_shader;

public:
  Sky() {
    /*
    *sun_shader = Shader("res/shaders/5.2.light_cube.vs",
                         "res/shaders/5.2.light_cube.fs");
                         */
    // prepare_render();
  }
  void prepare_render();
  void render();
};

#endif
