#pragma once

#include "gfx.hpp"
#include "shader.hpp"
#include "block.hpp"
#include "texture.hpp"
#include <map>
#include <string>

class Renderer {
    private:
        int windowWidth, windowHeight;
        std::map<std::string, Shader*> shaders;
        glm::mat4 model, view, projection;
    public:
        Renderer(int width, int height);
        void drawBlock();
        void attachShader(std::string, Shader *shader);
        Shader* getShaderByName(std::string);
};
