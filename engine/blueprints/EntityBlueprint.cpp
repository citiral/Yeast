//
// Created by Citiral on 27/06/2016.
//

#include "EntityBlueprint.h"
#include "../graphics/renderables/sprite.h"
#include "../resources/ResourceManager.h"
#include "../paths.h"

EntityBlueprint::EntityBlueprint(std::string& path) {
    std::ifstream file;
    file.open(FOLDER_ENTITIES + path + ".json", std::ifstream::in);

    json j(file);
    parseJson(j);

    file.close();
}

void EntityBlueprint::parseJson(json& j) {
    _renderable = RenderableBlueprint::from(j["renderable"]);
}

Entity* EntityBlueprint::create(Engine* engine, float x, float y) {
    return new Entity(engine, x, y, _renderable->create(engine));
}