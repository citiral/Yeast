//
// Created by Citiral on 2/07/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_RENDERABLEBACKGROUNDBLUEPRINT_H
#define I_WANNA_KILL_THE_BOSHY_RENDERABLEBACKGROUNDBLUEPRINT_H

#include "RenderableBlueprint.h"
#include "../Result.h"
#include <json.hpp>

using json = nlohmann::json;

class RenderableBackgroundBlueprint : public RenderableBlueprint {
public:
    RenderableBackgroundBlueprint(json& j);
    virtual Renderable* create(Engine* engine);

private:
    Result<std::string> _diffuse;
    Result<std::string> _normal;
    Result<float> _scale;
};


#endif //I_WANNA_KILL_THE_BOSHY_RENDERABLEBACKGROUNDBLUEPRINT_H
