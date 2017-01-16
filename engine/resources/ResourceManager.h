#pragma once

#include <map>
#include <utility>
#include <string>
#include <memory>
#include "resource.h"
#include "../graphics/primitives/program.h"
#include "../graphics/primitives/texture.h"
#include "resourceloader.h"
#include "../blueprints/WorldBlueprint.h"
#include "../blueprints/EntityBlueprint.h"
#include "../scripting/Script.h"
#include "../simplefilewatcher/FileWatcher.h"
#include "ResourceListener.h"

class ResourceManager {
public:
    ResourceManager(Engine* engine);
    ~ResourceManager();

    std::shared_ptr<Program> loadProgram(const char* vertex, const char* fragment);
    std::shared_ptr<GL30Texture> loadTexture(const char* path);
    //std::shared_ptr<WorldBlueprint> loadWorld(const char* path);
    //std::shared_ptr<EntityBlueprint> loadEntity(const char* path);
    std::shared_ptr<Script> loadScript(const char* path);

    std::shared_ptr<Program> loadProgram(const std::string& vertex, const std::string& fragment);
    std::shared_ptr<GL30Texture> loadTexture(const std::string& path);
    //std::shared_ptr<WorldBlueprint> loadWorld(const std::string& path);
    //std::shared_ptr<EntityBlueprint> loadEntity(const std::string& path);
    std::shared_ptr<Script> loadScript(const std::string& path);

    FW::FileWatcher* getFileWatcher();

private:
    Engine* _engine;

    ResourceLoader<std::pair<std::string, std::string>, Program> _programs;
    ResourceLoader<std::string, GL30Texture> _textures;
    ResourceLoader<std::string, WorldBlueprint> _worlds;
    ResourceLoader<std::string, EntityBlueprint> _entities;
    ResourceLoader<std::string, Script> _scripts;

    FW::FileWatcher* _fileWatcher;
};