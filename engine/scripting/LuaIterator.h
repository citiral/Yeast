//
// Created by Olivier on 7/21/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_LUAITERATOR_H
#define I_WANNA_KILL_THE_BOSHY_LUAITERATOR_H

#include <lua.hpp>
#include "LuaEngine.h"

template<class T>
class LuaIterator {
public:
    LuaIterator(T begin, T end): _cur(begin), _end(end) {};

    typename T::value_type value() {
        return *_cur;
    }

    void next() {
        _cur++;
    }

    bool ended() {
        return _cur == _end;
    }

    static int lua_value(lua_State* L) {
        LuaIterator<T> iter = LuaEngine::getValue<LuaIterator<T>>(L, 1);
        LuaEngine::pushValue(L, iter.value());
        return 1;
    }

    static int lua_next(lua_State* L) {
        LuaIterator<T> iter = LuaEngine::getValue<LuaIterator<T>>(L, 1);
        iter.next();

        if (iter.ended()) {
            lua_pushnil(L);
        } else {
            LuaEngine::pushValue(L, iter);
        }

        return 1;
    }

private:
    T _cur, _end;
};

#endif //I_WANNA_KILL_THE_BOSHY_LUAITERATOR_H
