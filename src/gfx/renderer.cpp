#include "renderer.hpp"
#include "shader.hpp"
#include "../state.hpp"

void Renderer2D::prepare(Shader *shader, CubeFace cb, Grass element) {
    auto texture_offset = element.texture_offset(cb.face);

    float minTX = this->textureAtlas.tW * texture_offset.x / this->textureAtlas.atlasW;
    float maxTX = this->textureAtlas.tW * (texture_offset.x + 1) / this->textureAtlas.atlasW;

    float minTY = this->textureAtlas.tH * texture_offset.y / this->textureAtlas.atlasH;
    float maxTY = this->textureAtlas.tH * (texture_offset.y + 1) / this->textureAtlas.atlasH;

    float vertices[] = {
        cb.vertices[0].x*cb.position.x, cb.vertices[0].y*cb.position.y, cb.vertices[0].z*cb.position.z, minTX, minTY,
        cb.vertices[1].x*cb.position.x, cb.vertices[1].y*cb.position.y, cb.vertices[1].z*cb.position.z, maxTX, minTY,
        cb.vertices[2].x*cb.position.x, cb.vertices[2].y*cb.position.y, cb.vertices[2].z*cb.position.z, minTX, maxTY,
        cb.vertices[3].x*cb.position.x, cb.vertices[3].y*cb.position.y, cb.vertices[3].z*cb.position.z, maxTX, maxTY,
    };
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QUAD_FACE_INDICES), QUAD_FACE_INDICES, GL_STATIC_DRAW);

    glBindVertexArray(this->vao);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Renderer2D::render(Shader *shader, Grass element, glm::vec3 position) {
    shader->use();

    shader->setMat4("projection", state.camera.projection);
    shader->setMat4("view", state.camera.view);

    for (const auto& cube_face : CUBE_FACES) {
        this->prepare(shader, cube_face, element);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
        glBindVertexArray(this->vao);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(state.camera.model, position);
        shader->setMat4("model", model);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}
