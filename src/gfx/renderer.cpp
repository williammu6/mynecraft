#include "renderer.hpp"

Renderer::Renderer(int width, int height) {
    windowWidth = width;
    windowHeight = height;

    model = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view  = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)windowWidth/ (float)windowHeight, 0.1f, 100.0f);
}

void Renderer::drawBlock() {
    Shader *shader = getShaderByName("block");
    shader->use();

    std::string path = "res/atlas1.png";
    unsigned int texture = createTextureFromPath(path);

    Block grass(texture);

    // create transformations
    // retrieve the matrix uniform locations
    unsigned int modelLoc = glGetUniformLocation(shader->program, "model");
    unsigned int viewLoc  = glGetUniformLocation(shader->program, "view");
    // pass them to the shaders (3 different ways)
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    shader->setMat4("projection", projection);

    grass.prepareDraw();
}

void Renderer::attachShader(std::string name, Shader *shader) {
    shaders[name] = shader;
}

Shader* Renderer::getShaderByName(std::string name) {
    return shaders[name];
}
