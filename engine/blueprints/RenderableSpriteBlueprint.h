//
// Created by Citiral on 2/07/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_RENDERABLESPRITEBLUEPRINT_H
#define I_WANNA_KILL_THE_BOSHY_RENDERABLESPRITEBLUEPRINT_H

#include "RenderableBlueprint.h"
#include "../Result.h"
#include <json.hpp>

using json = nlohmann::json;

class RenderableSpriteBlueprint : public RenderableBlueprint {
public:
    RenderableSpriteBlueprint(json& j);
    virtual Renderable* create(Engine* engine);

private:
    Result<std::string> _diffuse;
    Result<std::string> _normal;
    Result<bool> _lit;
};

#endif //I_WANNA_KILL_THE_BOSHY_RENDERABLESPRITEBLUEPRINT_H
