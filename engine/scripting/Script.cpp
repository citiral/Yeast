//
// Created by Citiral on 2/07/2016.
//

#include <iostream>
#include <cstring>
#include "Script.h"
#include "LuaEngine.h"
#include "../World.h"
#include "../Entity.h"
#include "../resources/ResourceManager.h"
#include "ScriptInstance.h"

Script::Script(const std::string& path): _path(path), _L(nullptr) {
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
        loadScript(engine);
    }

    // we go through the resource manager to load the script so we can get the same refcounted std::shared_ptr
    ScriptInstance* instance = new ScriptInstance(_L, engine->getResourceManager()->loadScript(_path.substr(std::strlen(FOLDER_SCRIPTS))));

    // get the function describing the script from the registry
    lua_pushstring(_L, _path.c_str());
    lua_gettable(_L, LUA_REGISTRYINDEX);

    // create a new environment and save it in the registry
    lua_pushlightuserdata(_L, instance);
    lua_newtable(_L); // environment table
    lua_newtable(_L); // environment metatable

    // we point metatable[__index] to the global table _G, so when a variable isn't found it will try to look in the global table
    lua_getglobal(_L, "_G");
    lua_setfield(_L, -2, "__index");

    // pops the metatable from the stack and then assigns it to the environment table
    lua_setmetatable(_L, -2);

    // we copy the environment table atop of the stack (it'll be a reference)
    lua_pushvalue(_L, -1);

    // then we assign the environment table to the script function, so it will be used to store the variables
    lua_setfenv(_L, -4);

    // and store the reference in the registry, so we can later access it as our script
    lua_rawset(_L, LUA_REGISTRYINDEX);

    // run the function using our new environment so it will be populated with the variables and functions inside the script
    if (lua_pcall(_L, 0, 0, 0)) {
        std::cout << "Error: " << lua_tostring(_L, -1) << std::endl;
    }

    return instance;
}

void Script::reloadInstance(Engine* engine, ScriptInstance* instance) {
    // get the file from the registry
    lua_pushstring(_L, _path.c_str());
    lua_gettable(_L, LUA_REGISTRYINDEX);

    // get the script instance table
    lua_pushlightuserdata(_L, instance);
    lua_gettable(_L, LUA_REGISTRYINDEX);

    // and assign it to the file as an environment
    lua_setfenv(_L, -2);

    // now execute the file to repopulate the script instance with the old variables
    if (lua_pcall(_L, 0, 0, 0)) {
        std::cout << "Error hotswapping " << _path << ": " << lua_tostring(_L, -1) << std::endl;
    }
}

void Script::loadScript(Engine* engine) {
    _L = engine->getLuaEngine()->getState();

    // load the file and store it in the registry
    lua_pushstring(_L, _path.c_str());
    luaL_loadfile(_L, _path.c_str());
    lua_settable(_L, LUA_REGISTRYINDEX);
}

bool Script::hotSwap(Engine* engine, const std::string& path) {
    // update the path
    _path = path;

    // reload the file to the registry
    loadScript(engine);

    // reload all scripts currently in the engine
    if (engine->getWorld()->getScript()->getScript().get() == this)
        reloadInstance(engine, engine->getWorld()->getScript());

    for (auto entity : engine->getWorld()->getEntities()) {
        for (auto script = entity->getScripts().begin() ; script != entity->getScripts().end() ; script++) {
            if (script->second->getScript().get() == this)
            reloadInstance(engine, script->second);
        }
    }

    return false;
}
