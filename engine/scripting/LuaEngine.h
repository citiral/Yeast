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

struct lua_constructor {
    unsigned int arguments;
    int (*func)(lua_State*);
};

template<class T>
struct LuaBindings {
    static const char name[];
    static lua_constructor constructors[];
    static luaL_reg functions[];
};

struct LuaEnumValue {
    const char* name;
    int value;
};

struct LuaCustomPush {
    virtual void push(lua_State* L, void* ptr) = 0;
};

template<bool isPointer, class T>
struct LuaEngineHelper {
};

template<class T>
struct LuaEngineHelper<false, T> {
    static_assert(!std::is_pointer<T>::value, "Dude this is a pointer type.");

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

template<> inline bool LuaEngineHelper<false, bool>::getValue(lua_State* _L, int index) {
    return (bool)lua_toboolean(_L, index);
}

template<class T>
inline T LuaEngineHelper<false, T>::getValue(lua_State* _L, int index) {
    return *(typename std::remove_reference<T>::type*)lua_touserdata(_L, index);
}

template<class T>
struct LuaEngineHelper<true, T> {
    static_assert(std::is_pointer<T>::value, "Dude this is no pointer type.");

    template<class F = T>

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
    void registerEnum(const char* name, LuaEnumValue* e);

    template<class T>
    void registerClass() {
        static_assert(std::is_standard_layout<T>::value, "Can only register standard_layout classes to lua.");
        // if there is at least one constructor, register the constructors
        if (LuaBindings<T>::constructors[0].func != nullptr)
            registerConstructors<T>(_L);

        // make the class and push a pointer for the registry store later
        lua_pushnumber(_L, typeid(T).hash_code());
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

        // and push its type
        lua_pushstring(_L, "_type");
        lua_pushnumber(_L, typeid(T).hash_code());
        lua_settable(_L, -3);

        // set the index operator
        lua_pushstring(_L, "__index");
        lua_pushvalue(_L, -2);
        lua_settable(_L, -3);

        // and store the table in the registry as registry[constructor<T>] = metatable
        lua_settable(_L, LUA_REGISTRYINDEX);

        // finally store its type in the global type array
        // we push it two-way so we can stringify the type
        lua_getglobal(_L, "Types");
        lua_pushstring(_L, LuaBindings<T>::name);
        lua_pushnumber(_L, typeid(T).hash_code());
        lua_settable(_L, -3);
        lua_pushnumber(_L, typeid(T).hash_code());
        lua_pushstring(_L, LuaBindings<T>::name);
        lua_settable(_L, -3);
        lua_pop(_L, 1);
     }

    template<class T>
    static void registerConstructors(lua_State* _L) {
        // push the main constructor function
        lua_pushcfunction(_L, &LuaEngine::constructor<T>);
        lua_setglobal(_L, LuaBindings<T>::name);

        // and register the constructor sub-functions
        lua_pushnumber(_L, -typeid(T).hash_code());
        lua_newtable(_L);
        for (int i = 0 ; LuaBindings<T>::constructors[i].func != nullptr ; i++) {
            lua_pushnumber(_L, LuaBindings<T>::constructors[i].arguments);
            lua_pushcfunction(_L, LuaBindings<T>::constructors[i].func);
            lua_settable(_L, -3);
        }
        lua_settable(_L, LUA_REGISTRYINDEX);
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

    template<class T>
    static int constructor(lua_State* _L) {
        // get the argument count before modifying the stack, otherwise it might be wrong
        int argc = lua_gettop(_L);

        // fetch the constructors table
        lua_pushnumber(_L, -typeid(T).hash_code());
        lua_gettable(_L, LUA_REGISTRYINDEX);

        // fetch the function with the given argument count
        lua_pushnumber(_L, argc);
        lua_gettable(_L, -2);

        // get the c function
        auto func = lua_tocfunction(_L, -1);

        // reset the stack
        lua_pop(_L, 2);

        // run the constructor function and return the amount of items it pushed on the stack (prop 1)
        return func(_L);
    }

    template<class T>
    static int destructor(lua_State* _L) {
        return LuaEngineHelper<std::is_pointer<T>::value, T>::destructor(_L);
    }

    template<class T>
    static void rawPushValue(lua_State* _L, T value) {
        // allocate a new class
        T* data = (T*)lua_newuserdata(_L, sizeof(T));
        new (data) T(value);

        // and its metatable
        lua_pushnumber(_L, typeid(T).hash_code());
        lua_gettable(_L, LUA_REGISTRYINDEX);

        lua_setmetatable(_L, -2);
    }

    // pushed values are automatically owned unless specifically pushed as unowned
    // if the class implements luacustompush, call that function to push the value, this adds support for polymorphism
    template<class T, class = typename std::enable_if<std::is_base_of<LuaCustomPush, T>::value && std::is_pointer<T>::value>::type>
    static void pushValue(lua_State* _L, T value) {
        value->push(_L, value);
    }

    // pushed values are automatically owned unless specifically pushed as unowned
    template<class T>
    static void pushValue(lua_State* _L, T value) {
        rawPushValue(_L, value);
    }

    // some wrappers around lua types so primitives can be pushed just like pointers
    static void pushValue(lua_State* _L, float value) {
        lua_pushnumber(_L, value);
    }

    // some wrappers around lua types so primitives can be pushed just like pointers
    static void pushValue(lua_State* _L, int value) {
        lua_pushnumber(_L, value);
    }

    // some wrappers around lua types so primitives can be pushed just like pointers
    static void pushValue(lua_State* _L, bool value) {
        lua_pushboolean(_L, value);
    }

    static void pushValue(lua_State* _L, const char* value) {
        lua_pushstring(_L, value);
    }

    // if the class implements luacustompush, call that function to push the value, this adds support for polymorphism
    template<class T>
    static typename std::enable_if<std::is_base_of<LuaCustomPush, typename std::remove_pointer<T>::type>::value>::type pushValueUnowned(lua_State* _L, T pointer) {
        static_assert(std::__is_pointer_helper<T>::value, "You can only push pointers unowned");
        // tag the pointer and call the push function
        pointer->push(_L, (void*)((size_t)pointer | 1));
    }

    template<class T>
    static typename std::enable_if<std::false_type::value == std::is_base_of<LuaCustomPush, typename std::remove_pointer<T>::type>::value>::type pushValueUnowned(lua_State* _L, T pointer) {
        static_assert(std::__is_pointer_helper<T>::value, "You can only push pointers unowned");
        // tag the pointer
        pointer = (T)((size_t)pointer | 1);
        rawPushValue(_L, pointer);
    }

    template<class T>
    static T getValue(lua_State* _L, int index) {
        return LuaEngineHelper<std::is_pointer<T>::value, T>::getValue(_L, index);
    }

private:
    lua_State* _L;
};


#endif //I_WANNA_KILL_THE_BOSHY_LUAENGINE_H
