//
// Created by Citiral on 14/07/2016.
//

#include <lua.hpp>
#include "../../math/Vector2.h"
#include "../LuaEngine.h"
#include "../EngineBindings.h"

template<>
const char LuaBindings<Vector2>::name[] = "Vector2";

template<>
luaL_reg LuaBindings<Vector2>::functions[] = {
        {"x", &BindFunction<Vector2, float>::ref<&Vector2::getX>},
        {"y", &BindFunction<Vector2, float>::ref<&Vector2::getY>},
        {"setX", &BindFunction<Vector2, void, float>::ref<&Vector2::setX>},
        {"setY", &BindFunction<Vector2, void, float>::ref<&Vector2::setY>},
        {"add",  &BindFunction<Vector2, Vector2, const Vector2&>::ref<&Vector2::operator+>},
        {"sub", &BindFunction<Vector2, Vector2, const Vector2&>::ref<&Vector2::operator- >},
        {"divide", &BindFunction<Vector2, Vector2, float>::ref<&Vector2::operator/>},
        {"multiply", &BindFunction<Vector2, Vector2, float>::ref<&Vector2::operator*>},
        {"clone", &BindFunction<Vector2, Vector2>::ref<&Vector2::clone>},
        {"length", &BindFunction<Vector2, float>::ref<&Vector2::length>},
        {"normalize", &BindFunction<Vector2, Vector2>::ref<&Vector2::normalize>},
        {"rotate", &BindFunction<Vector2, Vector2, float>::ref<&Vector2::rotate>},
        {"dot", &BindFunction<Vector2, float, const Vector2&>::ref<&Vector2::dot>},
        {0, 0}
};