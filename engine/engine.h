#pragma once

class Window;
class World;
class GraphicsContext;
class ResourceManager;
class Settings;
class LuaEngine;

class __declspec(dllexport) Engine {
public:
    Engine(int width, int height, bool fullscreen);
    ~Engine();

    Window* getWindow() const;
    GraphicsContext* getGraphicsContext();
    World* getWorld();
    Settings* getSettings();
    LuaEngine* getLuaEngine();

    void setWorld(World* world);

    ResourceManager* getResourceManager();

    void begin();

    void update(float dt);
    void render();
private:
    GraphicsContext* _gc;
    World* _world;
	Window* _window;
    ResourceManager* _loader;
    Settings* _settings;
    LuaEngine* _luaengine;
};