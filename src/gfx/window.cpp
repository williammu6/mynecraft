#include "window.hpp"
#include <iostream>

Window::Window(int width, int height) {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(width, height, "Title", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Error initializing OpenGL" << std::endl;
        exit(0);
    }

    glViewport(0, 0, width, height);

    glfwSwapInterval(1);
}

void Window::update() {
    processInput(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        terminate();
    }
}

Window* Window::create(const WindowProps& props) {
    return new Window(props.width, props.height);
}

void Window::terminate() {
    glfwSetWindowShouldClose(window, true);
    glfwDestroyWindow(window);
    glfwTerminate();
}

