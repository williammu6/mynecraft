#pragma once

#include "gfx.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include <map>
#include <string>

class Renderer {
    private:
        unsigned int vao, vbo, ebo, texture;
        int windowWidth, windowHeight;
        std::map<std::string, Shader*> shaders;
    public:
        Renderer(int width, int height);
        void drawBlock();
        void attachShader(std::string, Shader *shader);
        Shader* getShaderByName(std::string);
};
