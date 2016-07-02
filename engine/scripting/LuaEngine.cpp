//
// Created by Citiral on 2/07/2016.
//

#include "LuaEngine.h"

LuaEngine::LuaEngine() {
    _L = luaL_newstate();
    luaL_openlibs(_L);
}

LuaEngine::~LuaEngine() {
    lua_close(_L);
}


lua_State* LuaEngine::getState() {
    return _L;
}
