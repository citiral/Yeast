//
// Created by Citiral on 2/07/2016.
//

#include "RenderableBlueprint.h"
#include "RenderableSpriteBlueprint.h"
#include "RenderableBackgroundBlueprint.h"

RenderableBlueprint* RenderableBlueprint::from(nlohmann::json& j) {
    if (j["type"] == "sprite") {
        return new RenderableSpriteBlueprint(j);
    } else if (j["type"] == "background") {
        return new RenderableBackgroundBlueprint(j);
    } else {
        return nullptr;
    }
}
