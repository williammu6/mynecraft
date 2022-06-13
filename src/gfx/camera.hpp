#pragma once

#include "gfx.hpp"

struct Camera {
    int width, height;
    glm::mat4 view;
    float speed = 0.005f;
    // glm::vec3 cameraPos = glm::vec3(20.0f, 70.0f, 40.0f);
    glm::vec3 cameraPos = glm::vec3(0, 2, 10);

    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    glm::mat4 model = glm::mat4(1.0f);

    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 projection;

    glm::vec3 direction;

    float sensitivity = 0.1f;
    float lastX, lastY;
    float yaw = -90.0f;
    float pitch;

    Camera() {
        glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);
    };

    Camera(int width, int height) {
        this->width = width;
        this->height = height;
        lastX = (float)this->width / 2, lastY = (float)this->height / 2;

        direction.x = cos(glm::radians(yaw));
        direction.z = sin(glm::radians(yaw));

        glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
        projection = glm::mat4(1.0f);
        view = glm::mat4(1.0f);

        projection = glm::perspective(
            glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f),
                            glm::vec3(1.0f, 0.0f, 0.0f));
    }

    void lookAt(double xpos, double ypos) {
        float xoffset = xpos - this->lastX;
        float yoffset = this->lastY - ypos;
        this->lastX = xpos;
        this->lastY = ypos;

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        this->yaw += xoffset;
        this->pitch += yoffset;

        if (this->pitch > 89.0f) this->pitch = 89.0f;
        if (this->pitch < -89.0f) this->pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        this->cameraFront = glm::normalize(direction);
    }

    void update() {
        this->view =
            glm::lookAt(this->cameraPos, this->cameraPos + this->cameraFront,
                        this->cameraUp);
    }
};
