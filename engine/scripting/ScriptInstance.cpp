//
// Created by Citiral on 2/07/2016.
//

#include <iostream>
#include "ScriptInstance.h"

ScriptInstance::ScriptInstance(lua_State* L, std::shared_ptr<Script> script) {
    _L = L;
    _script = script;
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

    // remove the table from the stack
    lua_pop(_L, 1);
}

int ScriptInstance::lua(lua_State *L) {
    ScriptInstance* instance = LuaEngine::getValue<ScriptInstance*>(L, 1);
    lua_pushlightuserdata(L, instance);
    lua_gettable(L, LUA_REGISTRYINDEX);
    return 1;
}

std::shared_ptr<Script> ScriptInstance::getScript() {
    return _script;
}