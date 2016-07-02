//
// Created by Citiral on 2/07/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_SCRIPT_H
#define I_WANNA_KILL_THE_BOSHY_SCRIPT_H

#include <lua.hpp>
#include <string>
#include "../engine.h"
#include "ScriptInstance.h"

class Script {
public:
    Script(std::string& path);
    ~Script();

    ScriptInstance* createInstance(Engine* engine);

private:
    void initializeScript(Engine* engine);

    std::string _path;
    lua_State* _L;
};


#endif //I_WANNA_KILL_THE_BOSHY_SCRIPT_H
