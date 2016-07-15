//
// Created by Citiral on 6/07/2016.
//

#include "EngineBindings.h"
#include "../math/Vector2.h"
#include "../Entity.h"

template<> const char LuaBindings<Entity*>::name[] = "Entity";
template<> luaL_reg LuaBindings<Entity*>::functions[] = {
        {"x", &BindFunction<Entity, float>::ptr<&Entity::getX>},
        {"y", &BindFunction<Entity, float>::ptr<&Entity::getY>},
        {"setX", &BindFunction<Entity, void, float>::ptr<&Entity::setX>},
        {"setY", &BindFunction<Entity, void, float>::ptr<&Entity::setY>},
        {"pos", &BindFunction<Entity, Vector2&>::ptr<&Entity::getPosition>},
        {"setPos", &BindFunction<Entity, void, const Vector2&>::ptr<&Entity::setPosition>},
        {"rotation", &BindFunction<Entity, float>::ptr<&Entity::getRotation>},
        {"setRotation", &BindFunction<Entity, void, float>::ptr<&Entity::setRotation>},
        {0, 0}
};

template<> const char LuaBindings<Vector2>::name[] = "Vector2";
template<> luaL_reg LuaBindings<Vector2>::functions[] = {
        {"x", &BindFunction<Vector2, float>::ref<&Vector2::getX>},
        {"y", &BindFunction<Vector2, float>::ref<&Vector2::getY>},
        {"setX", &BindFunction<Vector2, void, float>::ref<&Vector2::setX>},
        {"setY", &BindFunction<Vector2, void, float>::ref<&Vector2::setY>},
        {"add",  &BindFunction<Vector2, Vector2, const Vector2&>::ref<&Vector2::operator+>},
        {"sub", &BindFunction<Vector2, Vector2, const Vector2&>::ref<&Vector2::operator- >},
        {"divide", &BindFunction<Vector2, Vector2, float>::ref<&Vector2::operator/>},
        {"multiply", &BindFunction<Vector2, Vector2, float>::ref<&Vector2::operator*>},
        {"clone", &BindFunction<Vector2, Vector2>::ref<&Vector2::clone>},
        {"length", &BindFunction<Vector2, float>::ref<&Vector2::length>},
        {"normalize", &BindFunction<Vector2, Vector2>::ref<&Vector2::normalize>},
        {"rotate", &BindFunction<Vector2, Vector2, float>::ref<&Vector2::rotate>},
        {"dot", &BindFunction<Vector2, float, const Vector2&>::ref<&Vector2::dot>},
        {0, 0}
};

template<> const char LuaBindings<Engine*>::name[] = "Engine";
template<> luaL_reg LuaBindings<Engine*>::functions[] = {
        {"window", &BindFunction<Engine, Window*>::ptr<&Engine::getWindow, false>},
        {"world", &BindFunction<Engine, World*>::ptr<&Engine::getWorld, false>},
        {"settings", &BindFunction<Engine, Settings*>::ptr<&Engine::getSettings, false>},
        {0, 0}
};

template<> const char LuaBindings<World*>::name[] = "World";
template<> luaL_reg LuaBindings<World*>::functions[] = {
        {"addEntity", &BindFunction<World, void, Entity*>::ptr<&World::addEntity>},
        {"removeEntity", &BindFunction<World, void, Entity*>::ptr<&World::removeEntity>},
        {0, 0}
};

template<> const char LuaBindings<Window*>::name[] = "Window";
template<> luaL_reg LuaBindings<Window*>::functions[] = {
        {"mouseX", &BindFunction<Window, int>::ptr<&Window::getMouseX>},
        {"mouseY", &BindFunction<Window, int>::ptr<&Window::getMouseY>},
        {"mousePos", &BindFunction<Window, Vector2>::ptr<&Window::getMousePos>},
        {"width", &BindFunction<Window, int>::ptr<&Window::getWidth>},
        {"height", &BindFunction<Window, int>::ptr<&Window::getHeight>},
        {"keyIsDown", &BindFunction<Window, bool, int>::ptr<&Window::keyIsDown>},
        {"buttonIsDown", &BindFunction<Window, bool, int>::ptr<&Window::buttonIsDown>},
        {0, 0}
};

void bind(LuaEngine* engine, lua_State* L) {
    engine->registerClass<Vector2>();
    engine->registerClass<Entity*>();
    engine->registerClass<Engine*>();
    engine->registerClass<World*>();
    engine->registerClass<Window*>();
}