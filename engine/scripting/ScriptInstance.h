//
// Created by Citiral on 2/07/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_SCRIPTINSTANCE_H
#define I_WANNA_KILL_THE_BOSHY_SCRIPTINSTANCE_H


#include <lua.hpp>

class ScriptInstance {
public:
    ScriptInstance(lua_State* L);
    ~ScriptInstance();

    void runFunction(const char* function);

private:
    lua_State* _L;
};


#endif //I_WANNA_KILL_THE_BOSHY_SCRIPTINSTANCE_H
