//
// Created by Citiral on 14/07/2016.
//

#include <lua.hpp>
#include "../../math/Vector2.h"
#include "../LuaEngine.h"
#include "../../Entity.h"
#include "../EngineBindings.h"
#include <functional>


int x(lua_State* L) {
    return 0;//wrapFunction<float, Entity>(&Entity::getX);
    //Entity* obj = LuaEngine::getValue<Entity>(L, 1);

    //lua_pushnumber(L, obj->getX());
    //return 1;
}

int y(lua_State* L) {
    Vector2* obj = LuaEngine::getValue<Vector2*>(L, 1);
    lua_pushnumber(L, obj->getY());
    return 1;
}

int setX(lua_State* L) {
    Vector2* obj = LuaEngine::getValue<Vector2*>(L, 1);
    obj->setX((float)lua_tonumber(L, 2));
    return 0;
}

int setY(lua_State* L) {
    Vector2* obj = LuaEngine::getValue<Vector2*>(L, 1);
    obj->setY((float)lua_tonumber(L, 2));
    return 0;
}

int rotation(lua_State* L) {
    Vector2* obj1 = LuaEngine::getValue<Vector2*>(L, 1);
    Vector2* obj2 = LuaEngine::getValue<Vector2*>(L, 2);
    LuaEngine::pushValue(L, new Vector2(obj1->getX() + obj2->getX(), obj1->getY() + obj2->getY()));
    return 1;
}

int setRotation(lua_State* L) {
    Vector2* obj1 = LuaEngine::getValue<Vector2*>(L, 1);
    Vector2* obj2 = LuaEngine::getValue<Vector2*>(L, 2);
    LuaEngine::pushValue(L, new Vector2(obj1->getX() - obj2->getX(), obj1->getY() - obj2->getY()));
    return 1;
}
template<>
const char LuaBindings<Entity>::name[] = "Entity";

template<>
luaL_reg LuaBindings<Entity>::functions[] = {
        {"x", &x},
        {"y", &y},
        {"setX", &setX},
        {"setY", &setY},
        {"rotation", &rotation},
        {"setRotation", &setRotation},
        {0, 0}
};