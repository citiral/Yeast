//
// Created by Citiral on 14/07/2016.
//

#include <lua.hpp>
#include <type_traits>
#include "../../math/Vector2.h"
#include "../LuaEngine.h"
#include "../EngineBindings.h"

int vector2_y(lua_State* L) {
    Vector2 obj = LuaEngine::getValue<Vector2>(L, 1);
    lua_pushnumber(L, obj.getY());
    return 1;
}

int vector2_setX(lua_State* L) {
    Vector2& obj = LuaEngine::getValue<Vector2&>(L, 1);
    obj.setX((float)lua_tonumber(L, 2));
    return 0;
}

int vector2_add(lua_State* L) {
    Vector2& obj1 = LuaEngine::getValue<Vector2&>(L, 1);
    Vector2& obj2 = LuaEngine::getValue<Vector2&>(L, 2);
    LuaEngine::pushValue(L, Vector2(obj1.getX() + obj2.getX(), obj1.getY() + obj2.getY()));
    return 1;
}

int vector2_sub(lua_State* L) {
    Vector2 obj1 = LuaEngine::getValue<Vector2>(L, 1);
    Vector2 obj2 = LuaEngine::getValue<Vector2>(L, 2);
    LuaEngine::pushValue(L, Vector2(obj1.getX() - obj2.getX(), obj1.getY() - obj2.getY()));
    return 1;
}

int vector2_divide(lua_State* L) {
    Vector2 obj1 = LuaEngine::getValue<Vector2>(L, 1);
    float s = (float)lua_tonumber(L, 2);
    LuaEngine::pushValue(L, new Vector2(obj1 / s));
    return 1;
}

int vector2_multiply(lua_State* L) {
    Vector2 obj1 = LuaEngine::getValue<Vector2>(L, 1);
    float s = (float)lua_tonumber(L, 2);
    LuaEngine::pushValue(L, new Vector2(obj1 * s));
    return 1;
}

int vector2_clone(lua_State* L) {
    Vector2 obj1 = LuaEngine::getValue<Vector2>(L, 1);
    LuaEngine::pushValue(L, new Vector2(obj1));
    return 1;
}

int vector2_length(lua_State* L) {
    Vector2 obj1 = LuaEngine::getValue<Vector2>(L, 1);
    lua_pushnumber(L, obj1.getLength());
    return 1;
}

int vector2_normalize(lua_State* L) {
    Vector2 obj1 = LuaEngine::getValue<Vector2>(L, 1);
    LuaEngine::pushValue(L, new Vector2(obj1.normalize()));
    return 1;
}

int vector2_rotate(lua_State* L) {
    Vector2 obj1 = LuaEngine::getValue<Vector2>(L, 1);
    float s = (float)lua_tonumber(L, 2);
    LuaEngine::pushValue(L, Vector2(obj1.rotate(s)));
    return 1;
}

int vector2_dot(lua_State* L) {
    Vector2 obj1 = LuaEngine::getValue<Vector2>(L, 1);
    Vector2 obj2 = LuaEngine::getValue<Vector2>(L, 2);
    lua_pushnumber(L, obj1.dot(obj2));
    return 1;
}

template<>
const char LuaBindings<Vector2>::name[] = "Vector2";

template<>
luaL_reg LuaBindings<Vector2>::functions[] = {
        {"x", &BindFunction<Vector2, float>::ref<&Vector2::getX>},
        {"y", &vector2_y},
        {"setX", &vector2_setX},
        {"setY", &BindFunction<Vector2, void, float>::ref<&Vector2::setY>},
        {"add",  &BindFunction<Vector2, Vector2, const Vector2&>::ref<&Vector2::operator+>},
        {"sub", &vector2_sub},
        {"divide", &vector2_divide},
        {"multiply", &vector2_multiply},
        {"clone", &vector2_clone},
        {"length", &vector2_length},
        {"normalize", &vector2_normalize},
        {"rotate", &vector2_rotate},
        {"dot", &vector2_dot},
        {0, 0}
};