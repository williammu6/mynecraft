#ifndef SKY_H
#define SKY_H

#include "../common.hpp"
#include "../gfx/gfx.hpp"
#include "../gfx/primitive.hpp"
#include "../state.hpp"

class Sky {
private:
  GLuint VAO, VBO, EBO;
  SkyShader *sky_shader;
  Primitive *primitive;

public:
  Sky() {
    SkyShader _sky_shader;
    // primitive = new Primitive();
    this->sky_shader = &_sky_shader;
    prepare_render();
  }
  void prepare_render();
  void render();
};

#endif
