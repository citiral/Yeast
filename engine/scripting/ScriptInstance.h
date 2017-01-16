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

    static int lua(lua_State* L);

    void runFunctionRec(int argcount) {
        // finally call the function with the counted amount of arguments
        if (lua_pcall(_L, argcount, 0, 0)) {
            std::cout << "Error: " << lua_tostring(_L, -1) << std::endl;
        }
    }

    template <class T, class... ARGS>
    void runFunctionRec(int argcount, T first, ARGS... args) {
        // push the current argument on the stack
        LuaEngine::pushValue(_L, first);

        // and continue recursing
        runFunctionRec(argcount+1, std::forward<ARGS>(args)...);
    }

    template <class... ARGS>
    void runFunction(const char* function, ARGS... args) {
        // first push the function on the stack
        lua_pushlightuserdata(_L, this);
        lua_gettable(_L, LUA_REGISTRYINDEX);
        lua_getfield(_L, -1, function);

        if (lua_isfunction(_L, -1)) {
            // then push all the arguments, and also call the function at the end
            runFunctionRec(0, std::forward<ARGS>(args)...);
        }

        // remove the table from the stack
        lua_pop(_L, 1);
    }

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
