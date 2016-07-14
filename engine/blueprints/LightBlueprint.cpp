//
// Created by Citiral on 2/07/2016.
//

#include "LightBlueprint.h"
#include "../graphics/lighting/PointLight.h"
#include "../graphics/lighting/AmbientLight.h"

LightBlueprint::LightBlueprint(json& j) {
    _type = j["type"];

    if (j.count("x")) _x = j["x"].get<float>();
    if (j.count("y")) _y = j["y"].get<float>();
    if (j.count("z")) _z = j["z"].get<float>();
    if (j.count("drop")) _drop = j["drop"].get<float>();
    if (j.count("end")) _end = j["end"].get<float>();
    if (j.count("depth")) _depth = j["depth"].get<float>();
    if (j.count("color")) {
        _color = Color(j["color"][0], j["color"][1], j["color"][2]);
    }
}

Light* LightBlueprint::create(Engine* engine) {
    if (_type == "point") {
        return new PointLight(engine, _color.value(), Vector2(_x.value(), _y.value()), _depth.value(), _drop.value(), _end.value());
    } else if (_type == "ambient") {
        return new AmbientLight(engine, _color.value());
    } else {
        assert(false);//todo
    }
}
