#pragma once

#include <string>

class Window;
class World;
class GraphicsContext;
class ResourceManager;
class Settings;
class LuaEngine;

class Engine {
public:
	Engine(const char* settings);
	Engine(int width, int height, bool fullscreen);
    ~Engine();

    Window* getWindow() const;
    GraphicsContext* getGraphicsContext();
    World* getWorld();
    Settings* getSettings();
    LuaEngine* getLuaEngine();

	void loadWorld(std::string path);

    ResourceManager* getResourceManager();

    void begin();

    void update(float dt);
    void render();

private:
    GraphicsContext* _gc;
	Window* _window;
    ResourceManager* _loader;
    Settings* _settings;
    LuaEngine* _luaengine;

    // The world that is currently loaded
    World* _world;

    // The world that is going to be loaded next update step, if any
    World* _nextWorld;
};