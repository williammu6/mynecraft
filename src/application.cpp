#include "application.hpp"
#include "common.hpp"

struct State global_state;
State &state = global_state;

Application::Application() {
    state.windowWidth = 800;
    state.windowHeight = 600;

    state.window = Window::create();
}

void Application::run() {
    state.running = true;
    state.renderer2d = Renderer2D();
    state.renderer2d.init();
    std::string path = "res/grass.png";
    state.renderer2d.textureAtlas = TextureAtlas(path);
    state.camera = Camera(state.windowWidth, state.windowHeight);

    Shader basicTexture("res/shaders/basicTexture.vert", "res/shaders/basicTexture.frag");

    while (state.running) {
        state.window->clear();

        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                state.renderer2d.render(&basicTexture, state.elements["grass"], glm::vec3(i, 0, j));

        inputHandler(state.window->p_getWindow());

        state.camera.update();
        state.window->update();
    }

    state.window->terminate();
}

void Application::inputHandler(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        state.running = false;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        state.wireframe_mode = !state.wireframe_mode;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        state.camera.cameraPos -= state.camera.speed * state.camera.cameraPos;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        state.camera.cameraPos += state.camera.speed * state.camera.cameraPos;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        state.camera.cameraPos -= glm::normalize(glm::cross(state.camera.cameraFront, state.camera.cameraUp)) * state.camera.speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        state.camera.cameraPos += glm::normalize(glm::cross(state.camera.cameraFront, state.camera.cameraUp)) * state.camera.speed;
}

Application::~Application() {
    state.window->terminate();
}
