//
// Created by Citiral on 27/06/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_WORLDBLUEPRINT_H
#define I_WANNA_KILL_THE_BOSHY_WORLDBLUEPRINT_H

#include "../World.h"
#include "LightBlueprint.h"
#include <string>
#include <vector>
#include <json.hpp>

using json = nlohmann::json;

class WorldBlueprint {
public:
    WorldBlueprint(std::string& path);
    World* create(Engine* engine);

private:
    void parseJson(json& j);

    struct EntityEntry {
        std::string name;
        float x;
        float y;
    };
    std::vector<EntityEntry> _entities;
    std::vector<LightBlueprint> _lights;
};


#endif //I_WANNA_KILL_THE_BOSHY_WORLDBLUEPRINT_H
