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

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    Resource<Program> loadProgram(const std::string& vertex, const std::string& fragment);
    Resource<GL30Texture> loadTexture(const std::string& path);
    Resource<WorldBlueprint> loadWorld(const std::string& path);
    Resource<EntityBlueprint> loadEntity(const std::string& path);
    Resource<Script> loadScript(const std::string& path);

private:
    ResourceLoader<std::pair<std::string, std::string>, Program> _programs;
    ResourceLoader<std::string, GL30Texture> _textures;
    ResourceLoader<std::string, WorldBlueprint> _worlds;
    ResourceLoader<std::string, EntityBlueprint> _entities;
    ResourceLoader<std::string, Script> _scripts;
};