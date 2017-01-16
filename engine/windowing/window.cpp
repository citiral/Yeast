#include "window.h"
#include <iostream>
#include <GLFW/glfw3.h>

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* glfwwindow, int key, int scancode, int action, int mods)
{
    Window* window = (Window*)glfwGetWindowUserPointer(glfwwindow);

    if (action == GLFW_PRESS)
        window->setKeyState(key, KeyState::PRESSED);
    else if (action == GLFW_RELEASE)
        window->setKeyState(key, KeyState::RELEASED);
}

static void mbutton_callback(GLFWwindow* glfwwindow, int button, int action, int mods)
{
    Window* window = (Window*)glfwGetWindowUserPointer(glfwwindow);

    if (action == GLFW_PRESS) {
        window->setButtonState(button, KeyState::PRESSED);
        std::cout << " mouse button pressed" << std::endl;
    } else if (action == GLFW_RELEASE)
        window->setButtonState(button, KeyState::RELEASED);
}

Window::Window() {
    _window = nullptr;
    for (int i = 0 ; i < GLFW_KEY_LAST ; i++) {
        _keystates[i] = KeyState::UP;
    }
    for (int i = 0 ; i < GLFW_MOUSE_BUTTON_LAST ; i++) {
        _buttonstates[i] = KeyState::UP;
    }
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
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


    if (_fullscreen)
        _window = glfwCreateWindow(_width, _height, "Tech demo 1", glfwGetPrimaryMonitor(), nullptr);
    else
        _window = glfwCreateWindow(_width, _height, "Tech demo 1", nullptr, nullptr);

    if (!_window) {
        std::cout << "Failed to initialize glfw" << std::endl;
    }

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);

    glfwSetWindowUserPointer(_window, this);
    glfwSetKeyCallback(_window, key_callback);
    glfwSetMouseButtonCallback(_window, mbutton_callback);
}

void Window::setResolution(int width, int height) {
    _width = width;
    _height = height;
}

void Window::setFullscreen(bool fullscreen) {
    _fullscreen = fullscreen;
}

bool Window::shouldClose() {
    return (bool)glfwWindowShouldClose(_window);
}

void Window::updateWindow() {
    glfwSwapBuffers(_window);
}

void Window::updateInput() {
    // decay all keystates
    decayInput(_keystates, GLFW_KEY_LAST);
    decayInput(_buttonstates, GLFW_MOUSE_BUTTON_LAST);

    // and then update them with new key pressed
    glfwPollEvents();

    double x, y;
    glfwGetCursorPos(_window, &x, &y);
    _mouseX = (int)x;
    _mouseY = (int)y;
}

void Window::decayInput(KeyState* array, size_t length) {
    for (size_t i = 0 ; i < length ; i++) {
        if (array[i] == KeyState::PRESSED)
            array[i] = KeyState::DOWN;
        else if (array[i] == KeyState::RELEASED)
            array[i] = KeyState::UP;
    }
}


bool Window::keyIsDown(int key) {
    return _keystates[key] == KeyState::DOWN;
}

bool Window::keyIsUp(int key) {
    return _keystates[key] == KeyState::UP;
}

bool Window::keyIsPressed(int key) {
    return _keystates[key] == KeyState::PRESSED;
}

bool Window::keyIsReleased(int key) {
    return _keystates[key] == KeyState::RELEASED;
}

bool Window::buttonIsDown(int key) {
    return _buttonstates[key] == KeyState::DOWN;
}

bool Window::buttonIsUp(int key) {
    return _buttonstates[key] == KeyState::UP;
}

bool Window::buttonIsPressed(int key) {
    return _buttonstates[key] == KeyState::PRESSED;
}

bool Window::buttonIsReleased(int key) {
    return _buttonstates[key] == KeyState::RELEASED;
}

int Window::getMouseX() {
    return _mouseX;
}

int Window::getMouseY() {
    return _mouseY;
}

Vector2 Window::getMousePos() {
    double x, y;
    glfwGetCursorPos(_window, &x, &y);
    return Vector2((float)x, (float)(_height - y));
}

int Window::getWidth() const {
	return _width;
}

int Window::getHeight() const {
	return _height;
}

void Window::setKeyState(int key, KeyState state) {
    _keystates[key] = state;
}

void Window::setButtonState(int key, KeyState state) {
    _buttonstates[key] = state;
}