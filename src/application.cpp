#include "application.hpp"
#include <iostream>

Application::Application() {
    m_Window = Window::create(600, 600);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };  

    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

    glGenVertexArrays(1, &m_VertexArray);  
    glBindVertexArray(m_VertexArray);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
}

Application::~Application() {
    getWindow()->terminate();
}

Window* Application::getWindow() { 
    return m_Window; 
}

void Application::run() {
    Window* window = getWindow();

    Shader shader2d("res/shaders/2d.vert", 
                    "res/shaders/2d.frag");

    shader2d.use();


    while (!window->shouldClose()) {
        window->clear();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        window->update();
    }
}
