#ifndef SHADER_H
#define SHADER_H

#include "gfx.hpp"
#include "../common.hpp"

class Shader
{
private:
  GLuint vertex_shader, fragment_shader;
  GLuint compile(std::string path, GLenum shader_type);
  std::string read_file(std::string path);

public:
  GLuint program;
  Shader(std::string vertex_path, std::string fragment_path);

  void use();

  void destroy();

  void setInt(const std::string &name, int value);
  void setFloat(const std::string &name, float value) const;
  void setBool(const std::string &name, bool value) const;
  void setVec2(const std::string &name, const glm::vec2 &value) const;
  void setVec3(const std::string &name, const glm::vec3 &value) const;
  void setVec4(const std::string &name, const glm::vec4 &value) const;
  void setMat2(const std::string &name, const glm::mat2 &mat) const;
  void setMat3(const std::string &name, const glm::mat3 &mat) const;
  void setMat4(const std::string &name, const glm::mat4 &mat) const;
};

#endif
