#pragma once

#include "shader.hpp"
#include "../element/element.hpp"
#include "../element/element.hpp"
#include "../common.hpp"

static glm::vec3 CUBE_F_B_VERTICES[] = {
    glm::vec3(-0.5, -0.5, 0.5), // TOP LEFT
    glm::vec3(0.5, -0.5, 0.5), // TOP RIGHT
    glm::vec3(-0.5, 0.5, 0.5),  // BOTTOM LEFT
    glm::vec3(0.5, 0.5, 0.5)   // BOTTOM RIGHT
};

static glm::vec3 CUBE_L_R_VERTICES[] = {
    glm::vec3(-0.5, -0.5, -0.5), // TOP LEFT
    glm::vec3(-0.5, 0.5, -0.5), // TOP RIGHT
    glm::vec3(-0.5, -0.5, 0.5),  // BOTTOM LEFT
    glm::vec3(-0.5, 0.5, 0.5)   // BOTTOM RIGHT
};

static glm::vec3 CUBE_T_B_VERTICES[] = {
    glm::vec3(-0.5, 0.5, -0.5), // TOP LEFT
    glm::vec3(0.5, 0.5, -0.5), // TOP RIGHT
    glm::vec3(-0.5, 0.5, 0.5),  // BOTTOM LEFT
    glm::vec3(0.5, 0.5, 0.5)   // BOTTOM RIGHT
};

/*
static const glm::vec2 QUAD_FACE_TEXTURE_COORDS[] = {
    glm::vec2(1, 0),
    glm::vec2(1, 1),
    glm::vec2(1, 0),
    glm::vec2(0, 1)
};
*/

static const unsigned int QUAD_FACE_INDICES[] {  // note that we start from 0!
    0, 1, 2,   // first triangle
    1, 2, 3    // second triangle
}; 

struct FaceStruct {
    enum Face face;
    glm::vec3 *vertices;
    glm::vec3 position;
};

static const FaceStruct FACES[] = {
    // { TOP, glm::vec3(0, 1, 0) }, 
    { FRONT_BACK, CUBE_F_B_VERTICES, glm::vec3(1, 1, 1) },  // 
    { FRONT_BACK, CUBE_F_B_VERTICES, glm::vec3(1, 1, -1) },  // 
                                                             //
    { LEFT_RIGHT, CUBE_L_R_VERTICES, glm::vec3(1, 1, 1) },  // 
    { LEFT_RIGHT, CUBE_L_R_VERTICES, glm::vec3(-1, 1, 1) },  // 

    { TOP, CUBE_T_B_VERTICES, glm::vec3(1, 1, 1) },  // 
    { BOTTOM, CUBE_T_B_VERTICES, glm::vec3(1, -1, 1) },  // 

    // { FRONT_BACK, glm::vec3(1, 1, -1) }, 
    // { FRONT_BACK, glm::vec3(-1, 1, 1) }, 
    // { FRONT_BACK, glm::vec3(0, 1, 1) }, 
    // { BOTTOM, glm::vec3(0, -1, 0) }, 
};

namespace Renderer {
    struct Renderer2D {
        unsigned int vao, vbo, ebo;

        Renderer2D() {}

        void prepare(Shader *shader, FaceStruct f, void *vervices);
        void render(Shader *shader, glm::vec3 position, unsigned int texture);
    };
};
