#include "engine.h"
#include "graphics/graphicscontext.h"
#include "windowing/window.h"
#include "World.h"
#include "Timer.h"
#include "resources/ResourceManager.h"
#include <iostream>
#include <cstdlib>
#include "Settings.h"
#include "scripting/LuaEngine.h"

#define FPS 60

Engine::Engine(int width, int height, bool fullscreen) {
    _loader = new ResourceManager;
    _settings = new Settings;
    _luaengine = new LuaEngine();

    _window = new Window;
    _window->setResolution(width, height);
    _window->setFullscreen(fullscreen);
    _window->createWindow();

    _gc = new GraphicsContext(width, height);
    _world = nullptr;

    if (!_gc->initialize()) {
        std::cout << "Error initializing opengl";
        exit(1);
    }
}

Engine::~Engine() {

}

void Engine::setWorld(World* world) {
    std::cout << "changing world" << std::endl;
    if (_world != nullptr) {
		_world->removed();
        delete _world;
    }
    _world = world;
	_world->added();
}

World* Engine::getWorld() {
    return _world;
}

void Engine::update(float dt) {
    _world->update(dt);
}

void Engine::render() {
    _gc->setBackground(0, 0, 0);
    _gc->clear();
	_gc->beginStep1Composition();
    _world->renderComposite(*_gc);
	_gc->beginStep2Lighting();
    _world->renderLighting(*_gc);
}

GraphicsContext *Engine::getGraphicsContext() {
    return _gc;
}

Window* Engine::getWindow() const {
	return _window;
}

Settings* Engine::getSettings() {
    return _settings;
}

ResourceManager* Engine::getResourceManager() {
    return _loader;
}

LuaEngine* Engine::getLuaEngine() {
    return _luaengine;
}

void Engine::begin() {
    // seed the random generator
    std::srand(static_cast <unsigned> (std::time(0)));

    // setup the begin world
    setWorld(_loader->loadWorld(_settings->get("application", "world"))->create(this));

    // enter the core game loop
    Timer t;
    double lastRender = 0;

    while (!_window->shouldClose()) {
        double elapsed = t.getDeltaTimeSeconds();
        lastRender += elapsed;

        if (lastRender >= 1./FPS)
        {
            update(1.0f/FPS);
            render();
            _window->updateWindow();
            lastRender -= 1./FPS;
        }
    }
}
