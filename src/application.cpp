#include "application.hpp"

struct State global_state;
State &state = global_state;

Application::Application()
{
    state.windowWidth = 800;
    state.windowHeight = 600;

    state.window = Window::create();
}

void Application::run()
{
    state.running = true;
    state.renderer2d = Renderer::Renderer2D();
    state.camera = Camera(state.windowWidth, state.windowHeight);

    Shader basicTexture("res/shaders/basicTexture.vert", "res/shaders/basicTexture.frag");
    std::string path = "res/grass_atlas.png";
    unsigned int texture = createTextureFromPath(path);

    while (state.running) {
        state.window->clear();

        state.renderer2d.render(&basicTexture, glm::vec3(0, 0, 0), texture);

        inputHandler(state.window->p_getWindow());
        state.window->update();
    }

    state.window->terminate();
}

void Application::inputHandler(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        state.running = false;
}

Application::~Application()
{
    state.window->terminate();
}
