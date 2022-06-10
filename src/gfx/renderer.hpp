#pragma once

#include "shader.hpp"
#include "texture.hpp"
#include "../element/element.hpp"
#include "../element/grass.hpp"
#include "../common.hpp"

static glm::vec3 CUBE_F_B_VERTICES[] = {
    glm::vec3(-0.5, -0.5, 0.5),
    glm::vec3(0.5, -0.5, 0.5), 
    glm::vec3(-0.5, 0.5, 0.5), 
    glm::vec3(0.5, 0.5, 0.5)   
};

static glm::vec3 CUBE_L_R_VERTICES[] = {
    glm::vec3(-0.5, -0.5, -0.5), 
    glm::vec3(-0.5, 0.5, -0.5), 
    glm::vec3(-0.5, -0.5, 0.5),  
    glm::vec3(-0.5, 0.5, 0.5)   
};

static glm::vec3 CUBE_T_B_VERTICES[] = {
    glm::vec3(-0.5, 0.5, -0.5),
    glm::vec3(0.5, 0.5, -0.5), 
    glm::vec3(-0.5, 0.5, 0.5), 
    glm::vec3(0.5, 0.5, 0.5)   
};

static const unsigned int QUAD_FACE_INDICES[] {
    0, 1, 2, 1, 2, 3 
}; 

struct CubeFace {
    enum Face face;
    glm::vec3 *vertices;
    glm::vec3 position;
};

static const CubeFace CUBE_FACES[] = {
    { FRONT_BACK, CUBE_F_B_VERTICES, glm::vec3(1, 1, 1) },   
    { FRONT_BACK, CUBE_F_B_VERTICES, glm::vec3(1, 1, -1) },   

    { LEFT_RIGHT, CUBE_L_R_VERTICES, glm::vec3(1, 1, 1) },   
    { LEFT_RIGHT, CUBE_L_R_VERTICES, glm::vec3(-1, 1, 1) },   

    { TOP, CUBE_T_B_VERTICES, glm::vec3(1, 1, 1) },   
    { BOTTOM, CUBE_T_B_VERTICES, glm::vec3(1, -1, 1) },   
};

struct Renderer2D {
    unsigned int vao, vbo, ebo;

    TextureAtlas textureAtlas;

    Renderer2D() {
    }

    void prepare(Shader *shader, CubeFace cube_face, Grass element);
    void render(Shader *shader, Grass element, glm::vec3 position);
    void init() {
        glGenBuffers(1, &this->vbo);
        glGenBuffers(1, &this->ebo);
        glGenVertexArrays(1, &this->vao);  
    };
};
