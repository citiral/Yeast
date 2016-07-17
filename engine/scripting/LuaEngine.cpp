//
// Created by Citiral on 2/07/2016.
//

#include "LuaEngine.h"
#include "EngineBindings.h"

LuaEngine::LuaEngine() {
    _L = luaL_newstate();
    luaL_openlibs(_L);

    // create the type table
    lua_newtable(_L);
    lua_setglobal(_L, "Types");

    bind(this, _L);
}

LuaEngine::~LuaEngine() {
    lua_close(_L);
}


lua_State* LuaEngine::getState() {
    return _L;
}

void LuaEngine::registerEnum(const char* name, LuaEnumValue* e) {
    // first create a table for the enum
    lua_newtable(_L);

    // set each value
    for (int i = 0 ; e[i].name != nullptr; i++) {
        lua_pushstring(_L, e[i].name);
        lua_pushnumber(_L, e[i].value);
        lua_settable(_L, -3);
    }

    // and register it in the global table
    lua_setglobal(_L, name);
}