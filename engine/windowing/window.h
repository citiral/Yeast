#pragma once

class GLFWwindow;

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
	bool buttonIsDown(int mouse);
	int getMouseX();
	int getMouseY();
	
	int getWidth() const;
	int getHeight() const;
	
private:
    int _width;
    int _height;
    bool _fullscreen;
    GLFWwindow* _window;

};