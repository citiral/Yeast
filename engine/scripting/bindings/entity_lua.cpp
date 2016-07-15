//
// Created by Citiral on 14/07/2016.
//

#include <lua.hpp>
#include "../../math/Vector2.h"
#include "../LuaEngine.h"
#include "../../Entity.h"
#include "../EngineBindings.h"

template<>
const char LuaBindings<Entity*>::name[] = "Entity";

template<>
luaL_reg LuaBindings<Entity*>::functions[] = {
        {"x", &BindFunction<Entity, float>::ptr<&Entity::getX>},
        {"y", &BindFunction<Entity, float>::ptr<&Entity::getY>},
        {"setX", &BindFunction<Entity, void, float>::ptr<&Entity::setX>},
        {"setY", &BindFunction<Entity, void, float>::ptr<&Entity::setY>},
        {"pos", &BindFunction<Entity, Vector2&>::ptr<&Entity::getPosition>},
        {"setPos", &BindFunction<Entity, void, const Vector2&>::ptr<&Entity::setPosition>},
        {"rotation", &BindFunction<Entity, float>::ptr<&Entity::getRotation>},
        {"setRotation", &BindFunction<Entity, void, float>::ptr<&Entity::setRotation>},
        {0, 0}
};