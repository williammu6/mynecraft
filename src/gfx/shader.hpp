#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <assert.h>

#include "gfx.hpp"

struct VertexAttributes {
    GLint size;
    const GLchar* attr;
};

class Shader {
  private:
    GLuint vertex_shader, fragment_shader;
    GLuint compile(std::string, GLenum);
    const char* read_file(std::string path);
  public:
    GLuint program;
    Shader(std::string vertex_path, std::string fragment_path);
    void use();
};

#endif
