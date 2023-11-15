#include "shader.hpp"
#include "../state.hpp"
#include "blockOutline.hpp"

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
  std::ifstream shaderFile;

  shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    shaderFile.open(path);
    std::stringstream shaderStream;

    shaderStream << shaderFile.rdbuf();

    shaderFile.close();

    code = shaderStream.str();
  } catch (std::ifstream::failure e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }

  return code;
}

void Shader::use() const {
  glUseProgram(program);
}

void Shader::destroy() const {
  glDeleteProgram(program);
}

void BlockShader::setUniforms(glm::vec3 position) {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(state.camera.model, position);
  setUniform("model", model);
  setUniform("view", state.camera.view);
  setUniform("projection", state.camera.projection);

  setUniform("light.direction", glm::vec3(-0.2f, 1.0f, 0.3f));
  // setUniform("light.position", glm::vec3(0, 100, 0));
  setUniform("light.ambient", glm::vec3(0.3));
  setUniform("light.diffuse", glm::vec3(0.5f));
  setUniform("light.specular", glm::vec3(1.0f));
  setUniform("light.color", glm::vec3(1.0f));
}

void CrosshairShader::setUniforms(glm::vec3 position) {
  glm::mat4 model = glm::mat4(1.0f);

  model = glm::scale(model, glm::vec3(0.05f));

  glm::mat4 projection = glm::ortho(-state.aspectRatio, state.aspectRatio,
                                    -1.0f, 1.0f, -1.0f, 1.0f);

  setUniform("projection", projection);
  setUniform("model", model);
}

void BlockOutlineShader::setUniforms(glm::vec3 position) {
  glm::mat4 model = glm::mat4(1.0f);

  model = glm::translate(state.camera.model, position);
  model = glm::scale(model, glm::vec3(1.015f));

  setUniform("view", state.camera.view);
  setUniform("projection", state.camera.projection);
  setUniform("model", model);
}

void RayShader::setUniforms(glm::vec3 position) {
  glm::mat4 model = glm::mat4(1.0f);

  model = glm::translate(state.camera.model, position);
  model = glm::scale(model, glm::vec3(1.2));

  setUniform("view", state.camera.view);
  setUniform("projection", state.camera.projection);
  setUniform("model", model);
}
