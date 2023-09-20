#include "shader.hpp"

Shader::Shader(std::string vertex_path, std::string fragment_path) {
  char infoLog[512];

  vertex_shader = compile(vertex_path, GL_VERTEX_SHADER);
  fragment_shader = compile(fragment_path, GL_FRAGMENT_SHADER);

  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  glLinkProgram(program);

  GLint linked;
  glGetProgramiv(program, GL_LINK_STATUS, &linked);

  if (!linked) {
    std::cout << "Error linking program" << std::endl;
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    std::cout << infoLog << std::endl;
    glDeleteProgram(program);
    exit(EXIT_FAILURE);
  }
}

GLuint Shader::compile(std::string path, GLenum shader_type) {
  std::string shader_code = read_file(path);
  const char *shader_codec = shader_code.c_str();

  GLuint shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, &shader_codec, NULL);
  glCompileShader(shader);

  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

  if (!status) {
    std::cout << "Error compiling shader" << std::endl;
    glDeleteShader(shader);
    exit(EXIT_FAILURE);
  }

  return shader;
}

std::string Shader::read_file(std::string path) {
  std::string code;
  std::ifstream shader_file;

  shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    shader_file.open(path);
    std::stringstream shader_stream;

    shader_stream << shader_file.rdbuf();

    shader_file.close();

    code = shader_stream.str();
  } catch (std::ifstream::failure e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }

  return code;
}

void Shader::use() { glUseProgram(program); }

void Shader::destroy() { glDeleteProgram(program); }

void Shader::setInt(const std::string &name, int value) {
  glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
  glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
  glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
  glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}

// ------------------------------------------------------------------------
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
  glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
  glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
  glUniformMatrix2fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}
