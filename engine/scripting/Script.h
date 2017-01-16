//
// Created by Citiral on 2/07/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_SCRIPT_H
#define I_WANNA_KILL_THE_BOSHY_SCRIPT_H

#include <lua.hpp>
#include <string>
#include "../engine.h"
#include "../resources/HotSwappable.h"

class ScriptInstance;

class Script {
public:
    Script(const std::string& path);
    ~Script();

    virtual bool hotSwap(Engine* engine, const std::string& path);

    ScriptInstance* createInstance(Engine* engine);
    void reloadInstance(Engine* engine, ScriptInstance* instance);

private:
    void loadScript(Engine* engine);

    std::string _path;
    lua_State* _L;
};


#endif //I_WANNA_KILL_THE_BOSHY_SCRIPT_H
