#pragma once

#include "../common.hpp"
#include "../element/grass.hpp"

#include "shader.hpp"
#include "texture.hpp"
#include "../element/element.hpp"
#include "../element/grass.hpp"

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

static const unsigned int QUAD_FACE_INDICES[6][6] = {
    { 2, 1, 0, 1, 2, 3 },
    { 0, 1, 2, 1, 3, 2 },
    { 0, 1, 2, 1, 3, 2 },
    { 2, 1, 0, 2, 3, 1 },
    { 2, 1, 0, 2, 3, 1 },
    { 0, 1, 2, 3, 2, 1 },
}; 

struct CubeFace {
    enum Face face;
    glm::vec3 position;

    glm::vec3* vertices() {
        switch (face) {
            case TOP:
                return CUBE_T_B_VERTICES;
            case FRONT_BACK:
                return CUBE_F_B_VERTICES;
            case LEFT_RIGHT:
                return CUBE_L_R_VERTICES;
            case BOTTOM:
                return CUBE_T_B_VERTICES;
        }
    }
};

static const CubeFace CUBE_FACES[] = {
    { TOP, glm::vec3(1, 1, 1) },   
    { FRONT_BACK,  glm::vec3(1, 1, 1) },   
    { LEFT_RIGHT,  glm::vec3(-1, 1, 1) },   
    { LEFT_RIGHT,  glm::vec3(1, 1, 1) },   
    { FRONT_BACK,  glm::vec3(1, 1, -1) },   
    { BOTTOM, glm::vec3(1, -1, 1) },
};

struct Block {
    // Grass element;
    int isBlock;
    glm::vec3 normalPosition;
    glm::vec3 position;
};

struct Chunk {
    glm::vec3 dimentions;
    Shader *shader;
    TextureAtlas textureAtlas;
    glm::vec3 position;

    int seaLevel = 64;
    unsigned int vao, vbo, ebo;
    std::vector<std::vector<std::vector<Block>>> blocks;

    Chunk(Shader *shader, TextureAtlas texture_atlas, glm::vec3 position) {
        this->dimentions = glm::vec3(16, 256, 16);
        this->shader = shader;
        this->position = position;
        this->textureAtlas = texture_atlas;

        this->init();
    };
    void init();
    void render();
    void prepare_face(CubeFace cf, Grass element, int idx);
    void render_face(Grass element, CubeFace cf, Block& block, int idx);
    void render_block(Grass element, Block& block);
};
