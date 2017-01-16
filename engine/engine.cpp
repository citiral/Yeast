#include "engine.h"
#include "graphics/graphicscontext.h"
#include "windowing/window.h"
#include "World.h"
#include "Timer.h"
#include "resources/ResourceManager.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include "Settings.h"
#include "scripting/LuaEngine.h"
#include "paths.h"

#define FPS 60

Engine::Engine(const char* settings) {
    _settings = new Settings;
    _settings->load(settings);

    _loader = new ResourceManager(this);
    _luaengine = new LuaEngine();
    _luaengine->setGlobal("engine", this);

    _window = new Window;
    _window->setResolution(_settings->getT<int>("graphics", "resolution_x"), _settings->getT<int>("graphics", "resolution_y"));
    _window->setFullscreen(_settings->getT<bool>("graphics", "fullscreen"));
    _window->createWindow();

    _gc = new GraphicsContext(this, _settings->getT<int>("graphics", "resolution_x"), _settings->getT<int>("graphics", "resolution_y"));
    _world = nullptr;
    _nextWorld = nullptr;

    if (!_gc->initialize()) {
        std::cout << "Error initializing opengl";
        exit(1);
    }
}

Engine::Engine(int width, int height, bool fullscreen) {
    _loader = new ResourceManager(this);
    _settings = new Settings;
    _luaengine = new LuaEngine();
    _luaengine->setGlobal("engine", this);

    _window = new Window;
    _window->setResolution(width, height);
    _window->setFullscreen(fullscreen);
    _window->createWindow();

    _gc = new GraphicsContext(this, width, height);
    _world = nullptr;
    _nextWorld = nullptr;

    if (!_gc->initialize()) {
        std::cerr << "Error initializing opengl" << std::endl;
        exit(1);
    }
}

Engine::~Engine() {

}

void Engine::loadWorld(std::string path) {
    if (_nextWorld != nullptr) {
        delete _nextWorld;
    }
    _nextWorld = new World(this, _loader->loadScript(path)->createInstance(this));
}

World* Engine::getWorld() {
    return _world;
}

void Engine::update(float dt) {
    _world->update(dt);
}

void Engine::render() {
    //_gc->setBackground(0, 0, 0);
    _gc->clear();
	_gc->beginStep1Composition();
    _world->renderComposite(*_gc);
	_gc->beginStep2Lighting();
    _world->renderLighting(*_gc);
    _gc->beginStep3PostProcessing();
    _gc->PostTonemap();
    _gc->beginStep4Finalize();
    _gc->PostFinalize();
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
    loadWorld(_settings->get("application", "world"));

    // enter the core game loop
    Timer t;
    double lastRender = 0;

    while (!_window->shouldClose()) {
        if (_nextWorld != nullptr) {
            if (_world != nullptr) {
                _world->destroyed();
                delete _world;
            }
            _world = _nextWorld;
            _world->added();
            _nextWorld = nullptr;
        }

        double elapsed = t.getDeltaTimeSeconds();
        //lastRender += elapsed;

        //if (lastRender >= 1./FPS)
        //{
            _loader->getFileWatcher()->update();
            _luaengine->setGlobal("deltatime", elapsed);
            update((float)elapsed);
            render();
            _window->updateWindow();
            lastRender -= 1./FPS;
        //}
    }
}
