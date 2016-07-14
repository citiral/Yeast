//
// Created by Citiral on 6/07/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_ENGINEBINDINGS_H
#define I_WANNA_KILL_THE_BOSHY_ENGINEBINDINGS_H


#include <lua.hpp>
#include "LuaEngine.h"

void bind(LuaEngine* engine, lua_State* L);

// helper functions to bind c++ functions
inline int wrapFunctionRec(lua_State* L, std::function<void()> func, int depth) {
    func();
    return 0;
};

template<class R>
inline int wrapFunctionRec(lua_State* L, std::function<R()> func, int depth) {
    R ret = func();
    LuaEngine::pushValue(L, ret);
    return 1;
};

template<class R, class T, class... ARGS>
inline int wrapFunctionRec(lua_State* L, std::function<R(T, ARGS...)> f, int depth) {
    auto g = [&](ARGS... args)->R {
        return f(LuaEngine::getValue<T>(L, depth), std::forward<ARGS>(args)...);
    };

    return wrapFunctionRec(L, (std::function<R(ARGS...)>)g, depth+1);
};

template<class R, class T, class... ARGS>
inline int wrapFunctionPtr(lua_State* L, R (T::*func)(ARGS...)) {
    std::function<R(T*, ARGS...)> f = func;
    return wrapFunctionRec(L, f, 1);
};

template<class R, class T, class... ARGS>
inline int wrapFunctionRef(lua_State* L, R (T::*func)(ARGS...)) {
    std::function<R(T*, ARGS...)> f = func;

    auto g = [&](ARGS... args)->R {
        return f(&LuaEngine::getValue<T&>(L, 1), std::forward<ARGS>(args)...);
    };

    return wrapFunctionRec(L, (std::function<R(ARGS...)>)g, 2);
};

template<class T, class R, class... ARGS>
struct BindFunction {
    template <R (T::*F)(ARGS...) const>
    static int ref(lua_State* L) {
        return wrapFunctionRef(L, (typename std::decay<R(T::*)(ARGS...)>::type)F);
    }
    template <R (T::*F)(ARGS...)>
    static int ref(lua_State* L) {
        return wrapFunctionRef(L, F);
    }
    template <R (T::*F)(ARGS...) const>
    static int ptr(lua_State* L) {
        return wrapFunctionPtr(L, (typename std::decay<R(T::*)(ARGS...)>::type)F);
    }
    template <R (T::*F)(ARGS...)>
    static int ptr(lua_State* L) {
        return wrapFunctionPtr(L, F);
    }
};

#endif //I_WANNA_KILL_THE_BOSHY_ENGINEBINDINGS_H
