//
// Created by Citiral on 27/06/2016.
//

#include "WorldBlueprint.h"
#include <fstream>
#include "../resources/ResourceManager.h"

WorldBlueprint::WorldBlueprint(std::string& path) {
    std::ifstream file;
    file.open(path, std::ifstream::in);

    json j(file);
    parseJson(j);

    file.close();
}

World* WorldBlueprint::create(Engine* engine) {
    World* world = new World(engine);

    for (auto it = _entities.begin(); it != _entities.end(); ++it) {
        world->addEntity(engine->getResourceManager()->loadEntity((*it).name)->create(engine, (*it).x, (*it).y));
    }

    for (auto it = _lights.begin(); it != _lights.end(); ++it) {
        world->addLight((*it).create(engine));
    }

    return world;
}

void WorldBlueprint::parseJson(json& j) {
    for (json::iterator it = j["entities"].begin(); it != j["entities"].end(); ++it) {
        _entities.push_back({(*it)["name"], (*it)["x"], (*it)["y"]});
    }
    for (json::iterator it = j["lights"].begin(); it != j["lights"].end(); ++it) {
        _lights.push_back(LightBlueprint(*it));
    }
}
