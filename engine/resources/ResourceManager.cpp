#include "ResourceManager.h"
#include "../paths.h"

ResourceManager::ResourceManager(Engine* engine) {
    _engine = engine;
    _fileWatcher = new FW::FileWatcher();

    _fileWatcher->addWatch("res\\assets", new ResourceListener<GL30Texture>(&_textures, [this] (std::string& path, std::shared_ptr<GL30Texture> texture) {
        texture->hotSwap(path);
    }));

    _fileWatcher->addWatch("res\\scripts", new ResourceListener<Script>(&_scripts, [this] (std::string& path, std::shared_ptr<Script> script) {
        script->hotSwap(_engine, path);
    }));
}

ResourceManager::~ResourceManager() {
    _fileWatcher->removeWatch("res\\assets");
    _fileWatcher->removeWatch("res\\scripts");
}

std::shared_ptr<Program> ResourceManager::loadProgram(const char* vertex, const char* fragment) {
    return _programs.getResource(std::make_pair(formatPath(FOLDER_SHADERS + std::string(vertex)), formatPath(FOLDER_SHADERS + std::string(fragment))));
}

std::shared_ptr<GL30Texture> ResourceManager::loadTexture(const char* path) {
    return _textures.getResource(formatPath(FOLDER_ASSETS + std::string(path)));
}
/*
std::shared_ptr<WorldBlueprint> ResourceManager::loadWorld(const char* path) {
    return _worlds.getResource(std::string(path));
}

std::shared_ptr<EntityBlueprint> ResourceManager::loadEntity(const char* path) {
    return _entities.getResource(std::string(path));
}*/

std::shared_ptr<Script> ResourceManager::loadScript(const char* path) {
    return _scripts.getResource(formatPath(FOLDER_SCRIPTS + std::string(path)));
}

std::shared_ptr<Program> ResourceManager::loadProgram(const std::string& vertex, const std::string& fragment) {
    return _programs.getResource(std::make_pair(formatPath(FOLDER_SHADERS + vertex), formatPath(FOLDER_SHADERS + fragment)));
}

std::shared_ptr<GL30Texture> ResourceManager::loadTexture(const std::string& path) {
    return _textures.getResource(formatPath(FOLDER_ASSETS + path));
}
/*
std::shared_ptr<WorldBlueprint> ResourceManager::loadWorld(const std::string& path) {
    return _worlds.getResource(path);
}

std::shared_ptr<EntityBlueprint> ResourceManager::loadEntity(const std::string& path) {
    return _entities.getResource(path);
}*/

std::shared_ptr<Script> ResourceManager::loadScript(const std::string& path) {
    return _scripts.getResource(formatPath(FOLDER_SCRIPTS + path));
}

FW::FileWatcher* ResourceManager::getFileWatcher() {
    return _fileWatcher;
}
