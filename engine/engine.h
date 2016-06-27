#pragma once

class Window;
class World;
class GraphicsContext;
class ResourceManager;

class Engine {
public:
    Engine(int width, int height, bool fullscreen);
    ~Engine();

    void setGraphicsContext(GraphicsContext* graphicsContext);
    GraphicsContext* getGraphicsContext();
	
	void setWindow(Window* window);
	Window* getWindow() const;

    void setWorld(World* world);
    World* getWorld();

    ResourceManager* getResourceManager();

    void begin(World* entry);

    void update(float dt);
    void render();
private:
    GraphicsContext* _gc;
    World* _world;
	Window* _window;
    ResourceManager* _loader;
};