//
// Created by Citiral on 2/07/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_SCRIPTINSTANCE_H
#define I_WANNA_KILL_THE_BOSHY_SCRIPTINSTANCE_H


#include <lua.hpp>
#include <memory>
#include "LuaEngine.h"
#include "Script.h"

class ScriptInstance {
public:
    ScriptInstance(lua_State* L, std::shared_ptr<Script> script);
    ScriptInstance(const ScriptInstance& script) = delete;
    ScriptInstance(ScriptInstance&& script) = delete;
    ~ScriptInstance();

    ScriptInstance& operator=(const ScriptInstance& other) = delete;
    ScriptInstance& operator=(ScriptInstance&& other) = delete;

    std::shared_ptr<Script> getScript();

    void runFunction(const char* function);

    static int lua(lua_State* L);

    template<class T>
    void setValue(const char* name, T value) {
        // first get the script's table
        lua_pushlightuserdata(_L, this);
        lua_gettable(_L, LUA_REGISTRYINDEX);

        // and we can set the value
        lua_pushstring(_L, name);
        LuaEngine::pushValue(_L, value);
        lua_settable(_L, -3);

        // and clean up the stack
        lua_pop(_L, 1);
    }

private:
    lua_State* _L;
    std::shared_ptr<Script> _script;
};


#endif //I_WANNA_KILL_THE_BOSHY_SCRIPTINSTANCE_H
