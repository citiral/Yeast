//
// Created by Citiral on 6/07/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_ENGINEBINDINGS_H
#define I_WANNA_KILL_THE_BOSHY_ENGINEBINDINGS_H


#include <lua.hpp>
#include "LuaEngine.h"

void bind(LuaEngine* engine, lua_State* L);

// helper functions to bind c++ functions
template<bool returnOwned>
struct WrapFunction;

template<>
struct WrapFunction<true> {
    static int rec(lua_State* L, std::function<void()> func, int depth) {
        func();
        return 0;
    };

    template<class R>
    static int rec(lua_State* L, std::function<R()> func, int depth) {
        R ret = func();
        LuaEngine::pushValue(L, ret);

        return 1;
    };

    template<class R, class T, class... ARGS>
    static int rec(lua_State* L, std::function<R(T, ARGS...)> f, int depth) {
        auto g = [&](ARGS... args)->R {
            return f(LuaEngine::getValue<T>(L, depth), std::forward<ARGS>(args)...);
        };

        return rec(L, (std::function<R(ARGS...)>)g, depth+1);
    };
};

template<>
struct WrapFunction<false> {
    static int rec(lua_State* L, std::function<void()> func, int depth) {
        func();
        return 0;
    };

    template<class R>
    static int rec(lua_State* L, std::function<R()> func, int depth) {
        R ret = func();
        LuaEngine::pushValueUnowned(L, ret);

        return 1;
    };

    template<class R, class T, class... ARGS>
    static int rec(lua_State* L, std::function<R(T, ARGS...)> f, int depth) {
        auto g = [&](ARGS... args)->R {
            return f(LuaEngine::getValue<T>(L, depth), std::forward<ARGS>(args)...);
        };

        return rec(L, (std::function<R(ARGS...)>)g, depth+1);
    };
};


template<bool returnOwned, class R, class T, class... ARGS>
inline int wrapFunctionPtr(lua_State* L, R (T::*func)(ARGS...)) {
    std::function<R(T*, ARGS...)> f = func;
    return WrapFunction<returnOwned>::rec(L, f, 1);
};

template<bool returnOwned, class R, class T, class... ARGS>
inline int wrapFunctionRef(lua_State* L, R (T::*func)(ARGS...)) {
    std::function<R(T*, ARGS...)> f = func;

    auto g = [&](ARGS... args)->R {
        return f(&LuaEngine::getValue<T&>(L, 1), std::forward<ARGS>(args)...);
    };

    return WrapFunction<returnOwned>::rec(L, (std::function<R(ARGS...)>)g, 2);
};

template<bool returnOwned, class R, class T, class... ARGS>
inline int wrapFunctionShared(lua_State* L, R (T::*func)(ARGS...)) {
    std::function<R(T*, ARGS...)> f = func;

    auto g = [&](ARGS... args)->R {
        return f(&*LuaEngine::getValue<std::shared_ptr<T>>(L, 1), std::forward<ARGS>(args)...);
    };

    return WrapFunction<returnOwned>::rec(L, (std::function<R(ARGS...)>)g, 2);
};

template<class T, class R, class... ARGS>
struct BindFunction {
    template <R (T::*F)(ARGS...) const, bool returnOwned = true>
    static int ref(lua_State* L) {
        return wrapFunctionRef<returnOwned>(L, (typename std::decay<R(T::*)(ARGS...)>::type)F);
    }
    template <R (T::*F)(ARGS...), bool returnOwned = true>
    static int ref(lua_State* L) {
        return wrapFunctionRef<returnOwned>(L, F);
    }
    template <R (T::*F)(ARGS...) const, bool returnOwned = true>
    static int ptr(lua_State* L) {
        return wrapFunctionPtr<returnOwned>(L, (typename std::decay<R(T::*)(ARGS...)>::type)F);
    }
    template <R (T::*F)(ARGS...), bool returnOwned = true>
    static int ptr(lua_State* L) {
        return wrapFunctionPtr<returnOwned>(L, F);
    }
    template <R (T::*F)(ARGS...) const, bool returnOwned = true>
    static int shared(lua_State* L) {
        return wrapFunctionShared<returnOwned>(L, (typename std::decay<R(T::*)(ARGS...)>::type)F);
    }
    template <R (T::*F)(ARGS...), bool returnOwned = true>
    static int shared(lua_State* L) {
        return wrapFunctionShared<returnOwned>(L, F);
    }
};

#endif //I_WANNA_KILL_THE_BOSHY_ENGINEBINDINGS_H
