#pragma once

#include "../math/Vector2.h"

class GLFWwindow;

enum class KeyState {
    DOWN,
    UP,
    PRESSED,
    RELEASED
};

class Window {
public:
    Window();
    ~Window();

    void createWindow();
    void setResolution(int width, int height);
    void setFullscreen(bool fullscreen);
    bool shouldClose();
    void updateWindow();

    bool keyIsDown(int key);
    bool keyIsUp(int key);
    bool keyIsPressed(int key);
    bool keyIsReleased(int key);
    bool buttonIsDown(int mouse);
    bool buttonIsUp(int mouse);
    bool buttonIsPressed(int mouse);
    bool buttonIsReleased(int mouse);

    void setKeyState(int key, KeyState state);
    void setButtonState(int button, KeyState state);

	int getMouseX();
	int getMouseY();
    Vector2 getMousePos();
	
	int getWidth() const;
	int getHeight() const;
	
private:
    void decayInput(KeyState* array, size_t length);

    int _width;
    int _height;
    bool _fullscreen;
    GLFWwindow* _window;
    KeyState _keystates[348];
    KeyState _buttonstates[7];
	int _mouseX, _mouseY;
};