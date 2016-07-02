//
// Created by Citiral on 2/07/2016.
//

#include "RenderableBackgroundBlueprint.h"
#include "../resources/ResourceManager.h"
#include "../graphics/renderables/Background.h"
#include "../paths.h"

RenderableBackgroundBlueprint::RenderableBackgroundBlueprint(json& j) {
    if (j.count("diffuse")) {
        _diffuse = j["diffuse"].get<std::string>();
    }
    if (j.count("normal")) {
        _normal = j["normal"].get<std::string>();
    }
    if (j.count("scale")) {
        _scale = j["scale"].get<float>();
    } else {
        _scale = 1;
    }
}

Renderable* RenderableBackgroundBlueprint::create(Engine* engine) {
    Background* sprite = new Background(engine, engine->getResourceManager()->loadTexture(FOLDER_ASSETS + _diffuse.value()), _scale.value());
    if (_normal.is_some()) sprite->setNormal(engine->getResourceManager()->loadTexture(FOLDER_ASSETS + _normal.value()));

    return sprite;
}
