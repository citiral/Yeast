//
// Created by Citiral on 2/07/2016.
//

#include <iostream>
#include "ScriptInstance.h"

ScriptInstance::ScriptInstance(lua_State* L) {
    _L = L;
}

ScriptInstance::~ScriptInstance() {
    if (_L != nullptr) {
        // remove the table from the registry
        lua_pushlightuserdata(_L, this);
        lua_pushnil(_L);
        lua_settable(_L, LUA_REGISTRYINDEX);
    }
}

void ScriptInstance::runFunction(const char* function) {
    lua_pushlightuserdata(_L, this);
    lua_gettable(_L, LUA_REGISTRYINDEX);
    lua_getfield(_L, -1, function);

    // if the top value is a function run it
    if (lua_isfunction(_L, -1)) {
        // run the function using our new environment to set up the script
        if (lua_pcall(_L, 0, 0, 0)) {
            std::cout << "Error: " << lua_tostring(_L, -1) << std::endl;
        }
    }
}

/*void ScriptInstance::setValue(const char* name, float value) {
    // first get the function
    lua_pushlightuserdata(_L, this);
    lua_gettable(_L, LUA_REGISTRYINDEX);

    // and we can set the value
    lua_pushstring(_L, name);
    lua_pushnumber(_L, value);
    lua_settable(_L, -3);

    // and clean up the stack
    lua_pop(_L, 1);
}

void ScriptInstance::setValue(const char* name, const char* value) {
    // first get the function
    lua_pushlightuserdata(_L, this);
    lua_gettable(_L, LUA_REGISTRYINDEX);

    // and we can set the value
    lua_pushstring(_L, name);
    lua_pushstring(_L, value);
    lua_settable(_L, -3);

    // and clean up the stack
    lua_pop(_L, 1);
}

void ScriptInstance::setValue(const char* name, void* value) {
    // first get the function
    lua_pushlightuserdata(_L, this);
    lua_gettable(_L, LUA_REGISTRYINDEX);

    // and we can set the value
    lua_pushstring(_L, name);
    lua_pushlightuserdata(_L, value);
    lua_settable(_L, -3);

    // and clean up the stack
    lua_pop(_L, 1);
}
*/