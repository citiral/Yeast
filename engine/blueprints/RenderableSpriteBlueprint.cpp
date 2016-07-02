//
// Created by Citiral on 2/07/2016.
//

#include "RenderableSpriteBlueprint.h"
#include "../resources/ResourceManager.h"
#include "../graphics/renderables/sprite.h"
#include "../paths.h"

RenderableSpriteBlueprint::RenderableSpriteBlueprint(json& j) {
    if (j.count("diffuse")) {
        _diffuse = j["diffuse"].get<std::string>();
    }
    if (j.count("normal")) {
        _normal = j["normal"].get<std::string>();
    }
    if (j.count("lit")) {
        _lit = j["lit"].get<bool>();
    }
}

Renderable* RenderableSpriteBlueprint::create(Engine* engine) {
    Sprite* sprite = new Sprite(engine, engine->getResourceManager()->loadTexture(FOLDER_ASSETS + _diffuse.value()));
    if (_normal.is_some()) sprite->setNormal(engine->getResourceManager()->loadTexture(FOLDER_ASSETS + _normal.value()));
    if (_lit.is_some()) sprite->setLit(_lit.value());

    return sprite;
}
