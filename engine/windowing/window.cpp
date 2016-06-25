#include "window.h"
#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

Window::Window() {
    _window = nullptr;
}

Window::~Window() {
    if (_window != nullptr) {
        glfwDestroyWindow(_window);
    }
    glfwTerminate();
}

void Window::createWindow() {
    
    glfwSetErrorCallback(error_callback);
    
    glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    
    if (_fullscreen)
        _window = glfwCreateWindow(_width, _height, "Tech demo 1", glfwGetPrimaryMonitor(), nullptr);
    else
        _window = glfwCreateWindow(_width, _height, "Tech demo 1", nullptr, nullptr);

    if (!_window) {
        std::cout << "Failed to initialize glfw" << std::endl;
    }
    
    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);
}

void Window::setResolution(int width, int height) {
    _width = width;
    _height = height;
}

void Window::setFullscreen(bool fullscreen) {
    _fullscreen = fullscreen;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(_window);
}

void Window::updateWindow() {
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

bool Window::keyIsDown(int key) {
	return glfwGetKey(_window, key) == GLFW_PRESS;
}

bool Window::buttonIsDown(int mouse) {
	return glfwGetMouseButton(_window, mouse) == GLFW_PRESS;
}

int Window::getMouseX() {
	double x, y;
	glfwGetCursorPos(_window, &x, &y);
	return x;
}

int Window::getMouseY() {
	double x, y;
	glfwGetCursorPos(_window, &x, &y);
	return _height - y;
}

int Window::getWidth() const {
	return _width;
}

int Window::getHeight() const {
	return _height;
}