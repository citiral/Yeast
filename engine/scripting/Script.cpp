//
// Created by Citiral on 2/07/2016.
//

#include <iostream>
#include "Script.h"
#include "LuaEngine.h"

Script::Script(std::string& path): _L(nullptr), _path(path) {
}

Script::~Script() {
    // clear the script from the registry so it can be GC'd
    if (_L) {
        lua_pushstring(_L, _path.c_str());
        lua_pushnil(_L);
        lua_settable(_L, LUA_REGISTRYINDEX);
    }
}

ScriptInstance* Script::createInstance(Engine* engine) {
    if (_L == nullptr) {
        initializeScript(engine);
    }

    ScriptInstance* instance = new ScriptInstance(_L);

    // get the function describing the script from the registry
    lua_pushstring(_L, _path.c_str());
    lua_gettable(_L, LUA_REGISTRYINDEX);

    // create a new environment and save it in the registry
    lua_pushlightuserdata(_L, instance);
    lua_newtable(_L); // environment table
    lua_newtable(_L); // environment metatable
    lua_getglobal(_L, "_G");
    lua_setfield(_L, -2, "__index");
    lua_setmetatable(_L, -2);
    lua_pushvalue(_L, -1);
    lua_setfenv(_L, -4);
    lua_settable(_L, LUA_REGISTRYINDEX);

    // run the function using our new environment to set up the script
    if (lua_pcall(_L, 0, 0, 0)) {
        std::cout << "Error: " << lua_tostring(_L, -1) << std::endl;
    }

    return instance;
}

void Script::initializeScript(Engine* engine) {
    _L = engine->getLuaEngine()->getState();

    // load the file and store it in the registry
    lua_pushstring(_L, _path.c_str());
    luaL_loadfile(_L, _path.c_str());
    lua_settable(_L, LUA_REGISTRYINDEX);
}
