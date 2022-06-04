#include "window.hpp"

Window::Window(int width, int height) {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);

    glfwMakeContextCurrent(window);
}

void Window::loop() {
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

Window* Window::create(int width, int height) {
    return new Window(width, height);
}

void Window::terminate() {
    glfwTerminate();
}
