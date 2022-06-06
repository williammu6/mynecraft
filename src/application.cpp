#include "application.hpp"

#include <iostream>

Application::Application() {
    windowProps = {
        .width = 860,
        .height = 640,
    };

    m_Window = Window::create(windowProps);
    m_Renderer = Renderer::create(windowProps);
}

Application::~Application() {
    getWindow()->terminate();
}

Window* Application::getWindow() { 
    return m_Window; 
}

Renderer* Application::getRenderer() { 
    return m_Renderer; 
}

void Application::run() {
    Window* window = getWindow();

    Shader blockShader("res/shaders/block.vert", "res/shaders/block.frag");
    m_Renderer->attachShader("block", &blockShader);

    glEnable(GL_DEPTH_TEST);  

    int nbFrames = 0;
    float lastTime = 0;
    while (!window->shouldClose()) {
        double currentTime = glfwGetTime();
        double delta = currentTime - lastTime;
        nbFrames++;
        window->clear();

        m_Renderer->sceneUpdate();

        for(unsigned int i = 0; i < 10; i++) {
            for(unsigned int j = 0; j < 10; j++) {
                m_Renderer->drawBlock(glm::vec3(i, 0.0f, j)); 
            }
        }

        inputHandler(window->p_getWindow());
        window->update();

        if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago
            double fps = double(nbFrames) / delta;

            std::stringstream ss;
            ss << " [" << fps << " FPS]";

            glfwSetWindowTitle(window->p_getWindow(), ss.str().c_str());

            nbFrames = 0;
            lastTime = currentTime;
        }
    }

blockShader.destroy();
    window->terminate();
}

void Application::inputHandler(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_Renderer->moveForward();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_Renderer->moveBackwards();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_Renderer->moveLeft();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_Renderer->moveRight();
}
