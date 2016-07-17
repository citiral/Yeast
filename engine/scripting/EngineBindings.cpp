//
// Created by Citiral on 6/07/2016.
//

#include "EngineBindings.h"
#include "../math/Vector2.h"
#include "../Entity.h"
#include "../Settings.h"
#include "../graphics/renderables/sprite.h"
#include <GLFW/glfw3.h>




template<> const char LuaBindings<Entity*>::name[] = "Entity";
template<> lua_constructor LuaBindings<Entity*>::constructors[] = {
        {0, 0}
};
template<> luaL_reg LuaBindings<Entity*>::functions[] = {
        {"x", &BindFunction<Entity, float>::ptr<&Entity::getX>},
        {"y", &BindFunction<Entity, float>::ptr<&Entity::getY>},
        {"setX", &BindFunction<Entity, void, float>::ptr<&Entity::setX>},
        {"setY", &BindFunction<Entity, void, float>::ptr<&Entity::setY>},
        {"pos", &BindFunction<Entity, Vector2&>::ptr<&Entity::getPosition>},
        {"setPos", &BindFunction<Entity, void, const Vector2&>::ptr<&Entity::setPosition>},
        {"rotation", &BindFunction<Entity, float>::ptr<&Entity::getRotation>},
        {"setRotation", &BindFunction<Entity, void, float>::ptr<&Entity::setRotation>},
        {"renderable", &BindFunction<Entity, Renderable*>::ptr<&Entity::getRenderable, return_unowned_pointer::value>},
        {0, 0}
};




int vec2construct1(lua_State* L) {
    LuaEngine::pushValue(L, Vector2());
    return 1;
}

int vec2construct2(lua_State* L) {
    float x = LuaEngine::getValue<float>(L, 1);
    float y = LuaEngine::getValue<float>(L, 2);
    LuaEngine::pushValue(L, Vector2(x, y));
    return 1;
}

template<> const char LuaBindings<Vector2>::name[] = "Vector2";
template<> lua_constructor LuaBindings<Vector2>::constructors[] = {
        {0, &vec2construct1},
        {2, &vec2construct2},
        {0, 0}
};
template<> luaL_reg LuaBindings<Vector2>::functions[] = {
        {"x", &BindFunction<Vector2, float>::ref<&Vector2::getX>},
        {"y", &BindFunction<Vector2, float>::ref<&Vector2::getY>},
        {"setX", &BindFunction<Vector2, void, float>::ref<&Vector2::setX>},
        {"setY", &BindFunction<Vector2, void, float>::ref<&Vector2::setY>},
        {"__add",  &BindFunction<Vector2, Vector2, const Vector2&>::ref<&Vector2::operator+>},
        {"__sub", &BindFunction<Vector2, Vector2, const Vector2&>::ref<&Vector2::operator- >},
        {"__div", &BindFunction<Vector2, Vector2, float>::ref<&Vector2::operator/>},
        {"__mul", &BindFunction<Vector2, Vector2, float>::ref<&Vector2::operator*>},
        {"clone", &BindFunction<Vector2, Vector2>::ref<&Vector2::clone>},
        {"length", &BindFunction<Vector2, float>::ref<&Vector2::length>},
        {"normalize", &BindFunction<Vector2, Vector2>::ref<&Vector2::normalize>},
        {"rotate", &BindFunction<Vector2, Vector2, float>::ref<&Vector2::rotate>},
        {"dot", &BindFunction<Vector2, float, const Vector2&>::ref<&Vector2::dot>},
        {0, 0}
};




template<> const char LuaBindings<Engine*>::name[] = "Engine";
template<> lua_constructor LuaBindings<Engine*>::constructors[] = {
        {0, 0}
};
template<> luaL_reg LuaBindings<Engine*>::functions[] = {
        {"window", &BindFunction<Engine, Window*>::ptr<&Engine::getWindow, return_unowned_pointer::value>},
        {"world", &BindFunction<Engine, World*>::ptr<&Engine::getWorld, return_unowned_pointer::value>},
        {"settings", &BindFunction<Engine, Settings*>::ptr<&Engine::getSettings, return_unowned_pointer::value>},
        {0, 0}
};




template<> const char LuaBindings<World*>::name[] = "World";
template<> lua_constructor LuaBindings<World*>::constructors[] = {
        {0, 0}
};
template<> luaL_reg LuaBindings<World*>::functions[] = {
        {"addEntity", &BindFunction<World, void, Entity*>::ptr<&World::addEntity>},
        {"removeEntity", &BindFunction<World, void, Entity*>::ptr<&World::removeEntity>},
        {0, 0}
};




template<> const char LuaBindings<Window*>::name[] = "Window";
template<> lua_constructor LuaBindings<Window*>::constructors[] = {
        {0, 0}
};
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




template<> const char LuaBindings<Sprite*>::name[] = "Sprite";
template<> lua_constructor LuaBindings<Sprite*>::constructors[] = {
        {0, 0}
};
template<> luaL_reg LuaBindings<Sprite*>::functions[] = {
        {"origin", &BindFunction<Sprite, Vector2>::ptr<&Sprite::getOrigin>},
        {"setOrigin", &BindFunction<Sprite, void, const Vector2&>::ptr<&Sprite::setOrigin>},
        {"centerOrigin", &BindFunction<Sprite, void>::ptr<&Sprite::centerOrigin>},
        {"lit", &BindFunction<Sprite, bool>::ptr<&Sprite::getLit>},
        {"setLit", &BindFunction<Sprite, void, bool>::ptr<&Sprite::setLit>},
        {"diffuse", &BindFunction<Sprite, Resource<GL30Texture>>::ptr<&Sprite::getDiffuse>},
        {"normal", &BindFunction<Sprite, Resource<GL30Texture>>::ptr<&Sprite::getNormal>},
        {"setDiffuse", &BindFunction<Sprite, void, Resource<GL30Texture>>::ptr<&Sprite::setDiffuse>},
        {"setNormal", &BindFunction<Sprite, void, Resource<GL30Texture>>::ptr<&Sprite::setNormal>},
        {0, 0}
};





LuaEnumValue Keys[] = {
        {"unknown", GLFW_KEY_UNKNOWN},
        {"space", GLFW_KEY_SPACE},
        {"apostrophe", GLFW_KEY_APOSTROPHE},
        {"comma", GLFW_KEY_COMMA},
        {"minus", GLFW_KEY_MINUS},
        {"period", GLFW_KEY_PERIOD},
        {"slash", GLFW_KEY_SLASH},
        {"zero", GLFW_KEY_0},
        {"one", GLFW_KEY_1},
        {"two", GLFW_KEY_2},
        {"three", GLFW_KEY_3},
        {"four", GLFW_KEY_4},
        {"five", GLFW_KEY_5},
        {"six", GLFW_KEY_6},
        {"seven", GLFW_KEY_7},
        {"eight", GLFW_KEY_8},
        {"nine", GLFW_KEY_9},
        {"semicolon", GLFW_KEY_SEMICOLON},
        {"equal", GLFW_KEY_EQUAL},
        {"A", GLFW_KEY_A},
        {"B", GLFW_KEY_B},
        {"C", GLFW_KEY_C},
        {"D", GLFW_KEY_D},
        {"E", GLFW_KEY_E},
        {"F", GLFW_KEY_F},
        {"G", GLFW_KEY_G},
        {"H", GLFW_KEY_H},
        {"I", GLFW_KEY_I},
        {"J", GLFW_KEY_J},
        {"K", GLFW_KEY_K},
        {"L", GLFW_KEY_L},
        {"M", GLFW_KEY_M},
        {"N", GLFW_KEY_N},
        {"O", GLFW_KEY_O},
        {"P", GLFW_KEY_P},
        {"Q", GLFW_KEY_Q},
        {"R", GLFW_KEY_R},
        {"S", GLFW_KEY_S},
        {"T", GLFW_KEY_T},
        {"U", GLFW_KEY_U},
        {"V", GLFW_KEY_V},
        {"W", GLFW_KEY_W},
        {"X", GLFW_KEY_X},
        {"Y", GLFW_KEY_Y},
        {"Z", GLFW_KEY_Z},
        {"leftBracket", GLFW_KEY_LEFT_BRACKET},
        {"backslash", GLFW_KEY_BACKSLASH},
        {"rightBracket", GLFW_KEY_RIGHT_BRACKET},
        {"graveAccent", GLFW_KEY_GRAVE_ACCENT},
        {"worldOne", GLFW_KEY_WORLD_1},
        {"worldTwo", GLFW_KEY_WORLD_2},
        {"escape", GLFW_KEY_ESCAPE},
        {"enter", GLFW_KEY_ENTER},
        {"tab", GLFW_KEY_TAB},
        {"backspace", GLFW_KEY_BACKSPACE},
        {"insert", GLFW_KEY_INSERT},
        {"delete", GLFW_KEY_DELETE},
        {"right", GLFW_KEY_RIGHT},
        {"left", GLFW_KEY_LEFT},
        {"down", GLFW_KEY_DOWN},
        {"up", GLFW_KEY_UP},
        {"pageUp", GLFW_KEY_PAGE_UP},
        {"pageDown", GLFW_KEY_PAGE_DOWN},
        {"home", GLFW_KEY_HOME},
        {"end", GLFW_KEY_END},
        {"capsLock", GLFW_KEY_CAPS_LOCK},
        {"scrollLock", GLFW_KEY_SCROLL_LOCK},
        {"numLock", GLFW_KEY_NUM_LOCK},
        {"printScreen", GLFW_KEY_PRINT_SCREEN},
        {"pause", GLFW_KEY_PAUSE},
        {"F1", GLFW_KEY_F1},
        {"F2", GLFW_KEY_F2},
        {"F3", GLFW_KEY_F3},
        {"F4", GLFW_KEY_F4},
        {"F5", GLFW_KEY_F5},
        {"F6", GLFW_KEY_F6},
        {"F7", GLFW_KEY_F7},
        {"F8", GLFW_KEY_F8},
        {"F9", GLFW_KEY_F9},
        {"F10", GLFW_KEY_F10},
        {"F11", GLFW_KEY_F11},
        {"F12", GLFW_KEY_F12},
        {"F13", GLFW_KEY_F13},
        {"F14", GLFW_KEY_F14},
        {"F15", GLFW_KEY_F15},
        {"F16", GLFW_KEY_F16},
        {"F17", GLFW_KEY_F17},
        {"F18", GLFW_KEY_F18},
        {"F19", GLFW_KEY_F19},
        {"F20", GLFW_KEY_F20},
        {"F21", GLFW_KEY_F21},
        {"F22", GLFW_KEY_F22},
        {"F23", GLFW_KEY_F23},
        {"F24", GLFW_KEY_F24},
        {"F25", GLFW_KEY_F25},
        {"kpZero", GLFW_KEY_KP_0},
        {"kpOne", GLFW_KEY_KP_1},
        {"kpTwo", GLFW_KEY_KP_2},
        {"kpThree", GLFW_KEY_KP_3},
        {"kpFour", GLFW_KEY_KP_4},
        {"kpFive", GLFW_KEY_KP_5},
        {"kpSix", GLFW_KEY_KP_6},
        {"kpSeven", GLFW_KEY_KP_7},
        {"kpEight", GLFW_KEY_KP_8},
        {"kpNine", GLFW_KEY_KP_9},
        {"kpDecimal", GLFW_KEY_KP_DECIMAL},
        {"kpDivide", GLFW_KEY_KP_DIVIDE},
        {"kpMultiply", GLFW_KEY_KP_MULTIPLY},
        {"kpSubtract", GLFW_KEY_KP_SUBTRACT},
        {"kpAdd", GLFW_KEY_KP_ADD},
        {"kpEnter", GLFW_KEY_KP_ENTER},
        {"kpEqual", GLFW_KEY_KP_EQUAL},
        {"leftShift", GLFW_KEY_LEFT_SHIFT},
        {"leftControl", GLFW_KEY_LEFT_CONTROL},
        {"leftAlt", GLFW_KEY_LEFT_ALT},
        {"leftSuper", GLFW_KEY_LEFT_SUPER},
        {"rightShift", GLFW_KEY_RIGHT_SHIFT},
        {"rightControl", GLFW_KEY_RIGHT_CONTROL},
        {"rightAlt", GLFW_KEY_RIGHT_ALT},
        {"rightSuper", GLFW_KEY_RIGHT_SUPER},
        {"menu", GLFW_KEY_MENU},
        {"last", GLFW_KEY_LAST},
        {0, 0}
};

LuaEnumValue Buttons[] = {
        {"mouse1", GLFW_MOUSE_BUTTON_1},
        {"mouse2", GLFW_MOUSE_BUTTON_2},
        {"mouse3", GLFW_MOUSE_BUTTON_3},
        {"mouse4", GLFW_MOUSE_BUTTON_4},
        {"mouse5", GLFW_MOUSE_BUTTON_5},
        {"mouse6", GLFW_MOUSE_BUTTON_6},
        {"mouse7", GLFW_MOUSE_BUTTON_7},
        {"mouse8", GLFW_MOUSE_BUTTON_8},
        {"last", GLFW_MOUSE_BUTTON_LAST},
        {"left", GLFW_MOUSE_BUTTON_LEFT},
        {"right", GLFW_MOUSE_BUTTON_RIGHT},
        {"middle", GLFW_MOUSE_BUTTON_MIDDLE},
        {0, 0}
};

void bind(LuaEngine* engine, lua_State* L) {
    engine->registerClass<Vector2>();
    engine->registerClass<Entity*>();
    engine->registerClass<Engine*>();
    engine->registerClass<World*>();
    engine->registerClass<Window*>();
    engine->registerClass<Sprite*>();
    engine->registerEnum("Keys", Keys);
    engine->registerEnum("Buttons", Buttons);
}