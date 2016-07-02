//
// Created by Citiral on 2/07/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_RENDERABLEBLUEPRINT_H
#define I_WANNA_KILL_THE_BOSHY_RENDERABLEBLUEPRINT_H

#include "../engine.h"
#include "../graphics/renderables/renderable.h"
#include <json.hpp>

class RenderableBlueprint {
public:
    virtual Renderable* create(Engine* engine) = 0;

    static RenderableBlueprint* from(nlohmann::json& j);
};

#endif //I_WANNA_KILL_THE_BOSHY_RENDERABLEBLUEPRINT_H
