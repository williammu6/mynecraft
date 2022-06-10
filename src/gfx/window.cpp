#include "window.hpp"
#include "../state.hpp"
#include <iostream>

Window::Window()
{
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(state.windowWidth, state.windowHeight, "Title", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Error initializing OpenGL" << std::endl;
        exit(0);
    }

    glEnable(GL_DEPTH_TEST);  
    glfwSwapInterval(1);
}

void Window::update()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::clear()
{
    glClearColor(0.4f, 0.9f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Window *Window::create()
{
    return new Window();
}

void Window::terminate()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow *Window::p_getWindow()
{
    return window;
}
