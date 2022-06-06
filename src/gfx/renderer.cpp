#include "renderer.hpp"

Renderer* Renderer::create(const WindowProps& windowProps) {
    return new Renderer(windowProps);
}

Renderer::Renderer(const WindowProps& windowProps) {
    windowWidth = windowProps.width;
    windowHeight = windowProps.height;

    model = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view  = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)windowWidth/ (float)windowHeight, 0.1f, 100.0f);

    std::string path = "res/grass_atlas.png";
    unsigned int texture = createTextureFromPath(path);
    blocks["grass"] = new Block(texture);
}

void Renderer::drawBlock(glm::vec3 position) {
    Shader *shader = getShaderByName("block");
    shader->use();
    shader->prepare3d(model, view, projection, position);
    blocks["grass"]->prepareDraw();
}

void Renderer::sceneUpdate() {
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Renderer::attachShader(std::string name, Shader *shader) {
    shaders[name] = shader;
}

Shader* Renderer::getShaderByName(std::string name) {
    return shaders[name];
}

void Renderer::moveForward() {
    cameraPos += cameraSpeed * cameraFront;
}

void Renderer::moveBackwards() {
    cameraPos -= cameraSpeed * cameraFront;
}

void Renderer::moveLeft() {
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Renderer::moveRight() {
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
