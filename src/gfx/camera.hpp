#pragma once

#include "gfx.hpp"

struct Camera {
    glm::mat4 view;
    glm::vec3 cameraPos = glm::vec3(0.0f, 40.0f, 20.0f);  
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 projection;

    Camera() {
        glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
        view          = glm::mat4(1.0f); 
        projection    = glm::mat4(1.0f);
    };

    Camera(int width, int height) {
        glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
        projection    = glm::mat4(1.0f);
        view          = glm::mat4(1.0f); 

        projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
    }
};
