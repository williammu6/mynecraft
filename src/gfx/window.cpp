#include "window.hpp"
#include <iostream>

void callback_name(int error_code, const char* description) {
    std::cout << description << std::endl;
}

Window::Window(int width, int height) {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(width, height, "Title", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Error initializing OpenGL" << std::endl;
        exit(0);
    }

    glfwSwapInterval(1);
}

void Window::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

Window* Window::create(int width, int height) {
    return new Window(width, height);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::terminate() {
    glfwTerminate();
}

