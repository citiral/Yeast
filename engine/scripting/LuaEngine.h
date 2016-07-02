//
// Created by Citiral on 2/07/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_LUAENGINE_H
#define I_WANNA_KILL_THE_BOSHY_LUAENGINE_H

#include <lua.hpp>


class LuaEngine {
public:
    LuaEngine();
    ~LuaEngine();

    lua_State* getState();

private:
    lua_State* _L;
};


#endif //I_WANNA_KILL_THE_BOSHY_LUAENGINE_H
