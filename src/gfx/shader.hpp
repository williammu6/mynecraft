#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <assert.h>

#include "gfx.hpp"
#include <glm/glm.hpp>

struct VertexAttributes {
    GLint size;
    const GLchar* attr;
};

class Shader {
  private:
    GLuint vertex_shader, fragment_shader;
    GLuint compile(std::string, GLenum);
    std::string read_file(std::string path);
  public:
    GLuint program;
    Shader(std::string vertex_path, std::string fragment_path);
    void use();
    void destroy();
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void prepare3d(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 position);
};

#endif
