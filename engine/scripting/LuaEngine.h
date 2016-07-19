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

/* TODO currently polymorphism does not properly differentiate between tagged/untagged pointers
 * really you should never push owned pointers to lua, I will probably remove that functionality to prevent confusion
 * if you want lua to own it use by value and if you want to share it use a shared pointer
*/

// extend std to acknowledge shared pointers in some functions
namespace std {
    template< class T > struct remove_pointer<shared_ptr<T>> { typedef T type;};
    template< class T > struct is_pointer<std::shared_ptr<T>> : std::true_type {};
}

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

template<class T>
struct LuaCustomPush {
    virtual void push(lua_State* L, T* val) = 0;
    virtual void push(lua_State* L, std::shared_ptr<T> val) = 0;
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
        T* obj = (T*)lua_touserdata(_L, 1);
        obj->~T();
        return 0;
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

    static void pushValue(lua_State* _L, float value) {
        lua_pushnumber(_L, value);
    }

    static void pushValue(lua_State* _L, int value) {
        lua_pushnumber(_L, value);
    }

    static void pushValue(lua_State* _L, bool value) {
        lua_pushboolean(_L, value);
    }

    static void pushValue(lua_State* _L, const char* value) {
        lua_pushstring(_L, value);
    }

    static void pushValue(lua_State* _L, std::string value) {
        lua_pushstring(_L, value.c_str());
    }

    // if the class implements luacustompush, call that function to push the value, this adds support for polymorphism
    template<class T>
    static typename std::enable_if<std::is_base_of<LuaCustomPush<typename std::remove_pointer<T>::type>, typename std::remove_pointer<T>::type>::value && std::is_pointer<T>::value>::type pushValue(lua_State* _L, T value) {
        value->push(_L, value);
    }

    template<class T>
    static typename std::enable_if<!(std::is_base_of<LuaCustomPush<typename std::remove_pointer<T>::type>, typename std::remove_pointer<T>::type>::value && std::is_pointer<T>::value)>::type pushValue(lua_State* _L, T value) {
        rawPushValue(_L, value);
    }

    template<class T>
    static T getValue(lua_State* _L, int index);

    template<class T>
    static T getGlobal(lua_State* _L, const char* name) {
        lua_pushstring(_L, name);
        lua_gettable(_L, LUA_GLOBALSINDEX);
        T t = getValue<T>(_L, -1);
        lua_pop(_L, 1);
        return t;
    }

private:
    lua_State* _L;
};

//TODO: expand this for all lua primary types, will do this once I need to :)
template<>
inline float LuaEngine::getValue<float>(lua_State* _L, int index) {
    return (float)lua_tonumber(_L, index);
}

template<>
inline int LuaEngine::getValue<int>(lua_State* _L, int index) {
    return (int)lua_tonumber(_L, index);
}

template<>
inline bool LuaEngine::getValue<bool>(lua_State* _L, int index) {
    return (bool)lua_toboolean(_L, index);
}

template<>
inline const char* LuaEngine::getValue<const char*>(lua_State* _L, int index) {
    return lua_tostring(_L, index);
}

template<>
inline std::string LuaEngine::getValue<std::string>(lua_State* _L, int index) {
    return std::string(lua_tostring(_L, index));
}

template<class T>
inline T LuaEngine::getValue(lua_State* _L, int index) {
    return *(typename std::remove_reference<T>::type*)lua_touserdata(_L, index);
}

#endif //I_WANNA_KILL_THE_BOSHY_LUAENGINE_H
