//
// Created by Citiral on 2/07/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_LUAENGINE_H
#define I_WANNA_KILL_THE_BOSHY_LUAENGINE_H

#include <lua.hpp>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <memory>
#include "../cdefs.h"

template<class T>
struct LuaBindings {
    static const char name[];
    static luaL_reg functions[];
};

template<bool isPointer, class T>
struct LuaEngineHelper {
};

template<class T>
struct LuaEngineHelper<false, T> {
    static_assert(!std::is_pointer<T>::value, "Dude this is a pointer type.");

    template<class F = T>
    static typename std::enable_if<std::is_default_constructible<F>::value, int>::type constructor(lua_State* _L) {
        // allocate a new class
        T* data = (T*)lua_newuserdata(_L, sizeof(T));
        new (data) T;

        // and its metatable
        lua_pushlightuserdata(_L, (void*)typeid(T).hash_code());
        lua_gettable(_L, LUA_REGISTRYINDEX);

        lua_setmetatable(_L, -2);

        return 1;
    }

    static int destructor(lua_State* _L) {
        T* obj = (T*)lua_touserdata(_L, 1);
        obj->~T();

        return 0;
    }

    static T getValue(lua_State* _L, int index);
};

//TODO: expand this for all lua primary types, will do this once I need to :)
template<> inline float LuaEngineHelper<false, float>::getValue(lua_State* _L, int index) {
    return (float)lua_tonumber(_L, index);
}

template<> inline int LuaEngineHelper<false, int>::getValue(lua_State* _L, int index) {
    return (int)lua_tonumber(_L, index);
}

template<class T>
inline T LuaEngineHelper<false, T>::getValue(lua_State* _L, int index) {
    return *(typename std::remove_reference<T>::type*)lua_touserdata(_L, index);
}

template<class T>
struct LuaEngineHelper<true, T> {
    static_assert(std::is_pointer<T>::value, "Dude this is no pointer type.");

    template<class F = T>
    static typename std::enable_if<std::is_default_constructible<typename std::remove_pointer<F>::type>::value, int>::type constructor(lua_State* _L) {
        // allocate a new class
        T* data = (T*)lua_newuserdata(_L, sizeof(T));
        *data = new typename std::pointer_traits<T>::element_type;

        // and its metatable
        lua_pushlightuserdata(_L, (void*)typeid(T).hash_code());
        lua_gettable(_L, LUA_REGISTRYINDEX);

        lua_setmetatable(_L, -2);

        return 1;
    }

    static int destructor(lua_State* _L) {
        T* obj = (T*)lua_touserdata(_L, 1);

        // only destroy it if it is not tagged
        if ((((size_t)*obj) & 1) == 0)
            delete *obj;

        return 0;
    }

    static T getValue(lua_State* _L, int index) {
        // get the object and untag it
        size_t obj = (size_t)*(T*)lua_touserdata(_L, index);
        return (T)(obj & ~(size_t)1);
    }
};

class LuaEngine {
public:
    LuaEngine();
    ~LuaEngine();

    lua_State* getState();

    template<class T>
    void registerClass() {
        static_assert(std::is_standard_layout<T>::value, "Can only register standard_layout classes to lua.");
        // push a global constructor if there is a default constructor
        if (std::is_default_constructible<typename std::remove_pointer<T>::type>::value)
            registerConstructor<T>(_L);

        // make the class and push a pointer for the registry store later
        lua_pushlightuserdata(_L, (void*)typeid(T).hash_code());
        luaL_newmetatable(_L, LuaBindings<T>::name);

        // set its destructor
        lua_pushstring(_L, "__gc");
        lua_pushcfunction(_L, &LuaEngine::destructor<T>);
        lua_settable(_L, -3);

        // set all the member functions
        for (int i = 0 ; LuaBindings<T>::functions[i].func != nullptr ; i++) {
            lua_pushstring(_L, LuaBindings<T>::functions[i].name);
            lua_pushcfunction(_L, LuaBindings<T>::functions[i].func);
            lua_settable(_L, -3);
        }

        // set the index operator
        lua_pushstring(_L, "__index");
        lua_pushvalue(_L, -2);
        lua_settable(_L, -3);

        // and store the table in the registry as registry[constructor<T>] = metatable
        lua_settable(_L, LUA_REGISTRYINDEX);
    }

    template<class T>
    static typename std::enable_if<std::is_default_constructible<typename std::remove_pointer<T>::type>::value>::type registerConstructor(lua_State* _L) {
        lua_pushcfunction(_L, &LuaEngine::constructor<T>);
        lua_setglobal(_L, LuaBindings<T>::name);
    }

    template<class T>
    static typename std::enable_if<!std::is_default_constructible<typename std::remove_pointer<T>::type>::value>::type registerConstructor(lua_State* _L) {
    }

    template<class T>
    void setGlobal(const char* name, T instance) {
        pushValue(_L, instance);
        lua_setglobal(_L, name);
    }

    template<class T>
    void setGlobalUnowned(const char* name, T instance) {
        pushValueUnowned(_L, instance);
        lua_setglobal(_L, name);
    }

    template<class T, class = typename std::enable_if<std::is_default_constructible<typename std::remove_pointer<T>::type>::value>::type>
    static int constructor(lua_State* _L) {
        return LuaEngineHelper<std::is_pointer<T>::value, T>::constructor(_L);
    }

    template<class T>
    static int destructor(lua_State* _L) {
        return LuaEngineHelper<std::is_pointer<T>::value, T>::destructor(_L);
    }

    // pushed values are automatically owned unless specifically pushed as unowned
    template<class T>
    static void pushValue(lua_State* _L, T value) {
        // allocate a new class
        T* data = (T*)lua_newuserdata(_L, sizeof(T));
        *data = value;

        // and its metatable
        lua_pushlightuserdata(_L, (void*)typeid(T).hash_code());
        lua_gettable(_L, LUA_REGISTRYINDEX);

        lua_setmetatable(_L, -2);
    }

    // some wrappers around lua types so primitives can be pushed just like pointers
    static void pushValue(lua_State* _L, float value) {
        lua_pushnumber(_L, value);
    }

    // some wrappers around lua types so primitives can be pushed just like pointers
    static void pushValue(lua_State* _L, int value) {
        lua_pushnumber(_L, value);
    }

    static void pushValue(lua_State* _L, const char* value) {
        lua_pushstring(_L, value);
    }

    template<class T>
    static void pushValueUnowned(lua_State* _L, T pointer) {
        static_assert(std::__is_pointer_helper<T>::value, "You can only push pointers unowned");
        // tag the pointer
        pointer = (T)((size_t)pointer | 1);

        // allocate a new class
        T* data = (T*)lua_newuserdata(_L, sizeof(T));
        *data = pointer;

        // and its metatable
        lua_pushlightuserdata(_L, (void*)typeid(T).hash_code());
        lua_gettable(_L, LUA_REGISTRYINDEX);

        lua_setmetatable(_L, -2);
    }

    template<class T>
    static T getValue(lua_State* _L, int index) {
        return LuaEngineHelper<std::is_pointer<T>::value, T>::getValue(_L, index);
    }

private:
    lua_State* _L;
};


#endif //I_WANNA_KILL_THE_BOSHY_LUAENGINE_H
