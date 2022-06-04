#include "application.hpp"
#include <iostream>

Application::Application() {
    m_Window = Window::create(600, 600);
}

Application::~Application() {
    getWindow()->terminate();
}

Window* Application::getWindow() { 
    return m_Window; 
}

void Application::run() {
    getWindow()->loop();
}
