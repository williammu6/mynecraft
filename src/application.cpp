#include "application.hpp"

#include "common.hpp"
#include "gfx/world/chunk.hpp"

struct State global_state;
State &state = global_state;

Application::Application() {
    state.windowWidth = 860;
    state.windowHeight = 640;

    state.window = Window::create();
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    state.camera.lookAt(xpos, ypos);
};

void Application::run() {
    state.running = true;
    std::string path = "res/textures.png";
    state.camera = Camera(state.windowWidth, state.windowHeight);

    Shader basicTexture("res/shaders/basicTexture.vert",
                        "res/shaders/basicTexture.frag");

    Chunk chunk = Chunk(&basicTexture, TextureAtlas(path), glm::vec3(1, 0, 1));

    double previousTime = glfwGetTime();
    int frameCount = 0;

    glfwSetInputMode(state.window->p_getWindow(), GLFW_CURSOR,
                     GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(state.window->p_getWindow(), mouse_callback);

    while (state.running) {
        float currentFrame = glfwGetTime();
        this->deltaTime = currentFrame - this->lastFrame;
        frameCount++;

        state.window->clear();

        chunk.render();

        state.camera.update();
        state.window->update();

        this->lastFrame = currentFrame;
        if (currentFrame - previousTime >= 1.0) {
            printf("FPS: %d\n", frameCount);
            frameCount = 0;
            previousTime = currentFrame;
        }

        inputHandler(state.window->p_getWindow());
    }

    state.window->terminate();
}

void Application::inputHandler(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        state.running = false;

    float cameraSpeed = 2.5f * this->deltaTime;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        state.wireframe_mode = !state.wireframe_mode;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        state.camera.cameraPos += cameraSpeed * state.camera.cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        state.camera.cameraPos -= cameraSpeed * state.camera.cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        state.camera.cameraPos -=
            glm::normalize(
                glm::cross(state.camera.cameraFront, state.camera.cameraUp)) *
            cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        state.camera.cameraPos +=
            glm::normalize(
                glm::cross(state.camera.cameraFront, state.camera.cameraUp)) *
            cameraSpeed;
}

Application::~Application() { state.window->terminate(); }
