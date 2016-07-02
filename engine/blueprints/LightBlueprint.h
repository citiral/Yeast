//
// Created by Citiral on 2/07/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_LIGHTBLUEPRINT_H
#define I_WANNA_KILL_THE_BOSHY_LIGHTBLUEPRINT_H

#include <string>
#include <json.hpp>
#include "../engine.h"
#include "../graphics/lighting/light.h"
#include "../Result.h"
#include "../graphics/primitives/color.h"

using json = nlohmann::json;

class LightBlueprint {
public:
    LightBlueprint(json& j);
    Light* create(Engine* engine);

private:
    std::string _type;
    Result<float> _x, _y, _z, _drop, _end, _depth;
    Result<Color> _color;
};


#endif //I_WANNA_KILL_THE_BOSHY_LIGHTBLUEPRINT_H
