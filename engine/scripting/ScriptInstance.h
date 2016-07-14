//
// Created by Citiral on 2/07/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_SCRIPTINSTANCE_H
#define I_WANNA_KILL_THE_BOSHY_SCRIPTINSTANCE_H


#include <lua.hpp>
#include "LuaEngine.h"

class ScriptInstance {
public:
    ScriptInstance(lua_State* L);
    ScriptInstance(const ScriptInstance& script) = delete;
    ScriptInstance(ScriptInstance&& script) = delete;
    ~ScriptInstance();

    ScriptInstance& operator=(const ScriptInstance& other) = delete;
    ScriptInstance& operator=(ScriptInstance&& other) = delete;

    void runFunction(const char* function);

    template<class T>
    void setValue(const char* name, T value) {
        // first get the function
        lua_pushlightuserdata(_L, this);
        lua_gettable(_L, LUA_REGISTRYINDEX);

        // and we can set the value
        lua_pushstring(_L, name);
        LuaEngine::pushValue(_L, value);
        lua_settable(_L, -3);

        // and clean up the stack
        lua_pop(_L, 1);
    }

    template<class T>
    void setValueUnowned(const char* name, T value) {
        // first get the function
        lua_pushlightuserdata(_L, this);
        lua_gettable(_L, LUA_REGISTRYINDEX);

        // and we can set the value
        lua_pushstring(_L, name);
        LuaEngine::pushPointerUnowned(_L, value);
        lua_settable(_L, -3);

        // and clean up the stack
        lua_pop(_L, 1);
    }

private:
    lua_State* _L;
};


#endif //I_WANNA_KILL_THE_BOSHY_SCRIPTINSTANCE_H
