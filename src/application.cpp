#include "application.hpp"
#include "gfx/renderer.hpp"

#include <iostream>

Application::Application() {
    shouldStop = false;

    windowProps = {
        .width = 1280,
        .height = 960,
    };

    m_Window = Window::create(windowProps);
}

Application::~Application() {
    getWindow()->terminate();
}

Window* Application::getWindow() { 
    return m_Window; 
}

void Application::stop() {
    shouldStop = true;
}

void Application::run() {
    Window* window = getWindow();

    Shader shader2d("res/shaders/2d.vert", 
                    "res/shaders/2d.frag");

    Renderer renderer(windowProps.width, windowProps.height);

    renderer.attachShader("block", &shader2d);

    glEnable(GL_DEPTH_TEST);  

    while (!window->shouldClose()) {
        window->clear();

        renderer.drawBlock();

        window->update();
    }

    shader2d.destroy();
    window->terminate();
}
