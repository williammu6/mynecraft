#include "renderer.hpp"
#include "shader.hpp"
#include "../state.hpp"

using namespace Renderer;

void Renderer2D::prepare(Shader *shader, FaceStruct f, void *asdf) {
    float vertices[] = {
        f.vertices[0].x*f.position.x, f.vertices[0].y*f.position.y, f.vertices[0].z*f.position.z, 0, 0,
        f.vertices[1].x*f.position.x, f.vertices[1].y*f.position.y, f.vertices[1].z*f.position.z, 1, 0,
        f.vertices[2].x*f.position.x, f.vertices[2].y*f.position.y, f.vertices[2].z*f.position.z, 0, 1,
        f.vertices[3].x*f.position.x, f.vertices[3].y*f.position.y, f.vertices[3].z*f.position.z, 1, 1,
    };
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &this->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QUAD_FACE_INDICES), QUAD_FACE_INDICES, GL_STATIC_DRAW);

    glGenVertexArrays(1, &this->vao);  
    glBindVertexArray(this->vao);

    int modelLocation = glGetUniformLocation(shader->program, "model");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(state.camera.model));
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Renderer2D::render(Shader *shader, glm::vec3 position, unsigned int texture) {
    shader->use();

    glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 projection    = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)state.windowWidth / (float)state.windowHeight, 0.1f, 100.0f);
    view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    // pass transformation matrices to the shader
    shader->setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    shader->setMat4("view", view);

    for (const auto& f : FACES) {
        this->prepare(shader, f, (float[]) { });

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
        glBindVertexArray(this->vao);   // glDrawArrays(GL_TRIANGLES, 0, 6);

        glm::mat4 model = glm::translate(state.camera.model, glm::vec3(0, 0, 0));
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));  
        shader->setMat4("model", model);
                                        //
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //
        // glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
