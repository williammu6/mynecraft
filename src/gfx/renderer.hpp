#pragma once

#include "gfx.hpp"
#include "shader.hpp"
#include "block.hpp"
#include "texture.hpp"
#include "window.hpp"
#include <map>
#include <string>

class Renderer {
    private:
        int windowWidth, windowHeight;
        std::map<std::string, Shader*> shaders;
        std::map<std::string, Block*> blocks;
        glm::mat4 model, view, projection;

        const float cameraSpeed = 0.5;
        glm::vec3 cameraPos   = glm::vec3(0.0f, 3.0f,  20.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    public:
        Renderer(const WindowProps& windowProps);
        static Renderer* create(const WindowProps& windowProps);
        void drawBlock(glm::vec3 position);
        void attachShader(std::string, Shader *shader);
        void sceneUpdate();
        Shader* getShaderByName(std::string);

        void moveForward();
        void moveBackwards();
        void moveLeft();
        void moveRight();
};
