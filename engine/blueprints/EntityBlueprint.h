//
// Created by Citiral on 27/06/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_ENTITYBLUEPRINT_H
#define I_WANNA_KILL_THE_BOSHY_ENTITYBLUEPRINT_H

#include <string>
#include "../Entity.h"
#include "../engine.h"
#include "RenderableBlueprint.h"
#include <json.hpp>

using json = nlohmann::json;

class EntityBlueprint {
public:
    EntityBlueprint(const std::string& path);
    Entity* create(Engine* engine, float x, float y);

private:
    void parseJson(json& j);
    RenderableBlueprint* _renderable;
    std::vector<std::string> _scripts;
};


#endif //I_WANNA_KILL_THE_BOSHY_ENTITYBLUEPRINT_H
