#ifndef SHADER_H
#define SHADER_H

#include "../common.hpp"
#include "gfx.hpp"

enum class Shaders { BLOCK = 0, CROSSHAIR, RAY, BLOCK_OUTLINE };

class Shader {
private:
  unsigned int program;
  unsigned int vertex_shader, fragment_shader;
  unsigned int compile(std::string path, GLenum shader_type);
  std::string read_file(std::string path);
  std::unordered_map<std::string, int> uniform_location_cache;

  int getUniformLocation(const std::string &name) {
    if (uniform_location_cache.find(name) != uniform_location_cache.end())
      return uniform_location_cache[name];
    int location = glGetUniformLocation(program, name.c_str());
    uniform_location_cache[name] = location;
    return location;
  }

  template <typename T>
  void setUniformInternal(unsigned int location, const T &value) const;
  // setUniforms methods
  template <>
  void setUniformInternal<int>(unsigned int location, const int &value) const {
    glUniform1i(location, value);
  }
  template <>
  void setUniformInternal<float>(unsigned int location,
                                 const float &value) const {
    glUniform1f(location, value);
  }
  template <>
  void setUniformInternal<glm::vec3>(unsigned int location,
                                     const glm::vec3 &value) const {
    glUniform3fv(location, 1, &value[0]);
  }
  template <>
  void setUniformInternal<glm::mat4>(unsigned int location,
                                     const glm::mat4 &value) const {
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
  }

public:
  Shader(std::string vertex_path, std::string fragment_path);

  void use() const;
  void destroy() const;
  virtual void setUniforms(glm::vec3 position) = 0;

  template <typename T>
  void setUniform(const std::string &name, const T &value) {
    int location = getUniformLocation(name);
    setUniformInternal(location, value);
  };
};

class BlockShader : public Shader {
public:
  BlockShader()
      : Shader("assets/shaders/block.vert", "assets/shaders/block.frag"){};

  void setUniforms(glm::vec3) override;
};

class CrosshairShader : public Shader {
public:
  CrosshairShader()
      : Shader("assets/shaders/crosshair.vert",
               "assets/shaders/crosshair.frag") {
  }

  void setUniforms(glm::vec3) override;
};

class BlockOutlineShader : public Shader {
public:
  BlockOutlineShader()
      : Shader("assets/shaders/blockOutline.vert",
               "assets/shaders/blockOutline.frag"){};

  void setUniforms(glm::vec3) override;
};

#endif
