#ifndef SHADER_H
#define SHADER_H

#include <assert.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "gfx.hpp"
#include <glm/glm.hpp>

struct VertexAttributes {
  GLint size;
  const GLchar *attr;
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
  void setInt(const std::string &name, int value);
  void setVec3(const std::string &name, const glm::vec3 &value) const;
  void setMat3(const std::string &name, const glm::mat3 &mat) const;
  void setMat4(const std::string &name, const glm::mat4 &mat) const;
};

#endif
