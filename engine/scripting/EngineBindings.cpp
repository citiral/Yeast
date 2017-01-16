//
// Created by Citiral on 6/07/2016.
//

#include "EngineBindings.h"
#include "../math/Vector2.h"
#include "../Entity.h"
#include "../Settings.h"
#include "../resources/ResourceManager.h"
#include "../graphics/renderables/sprite.h"
#include "../graphics/renderables/Background.h"
#include "../graphics/lighting/AmbientLight.h"
#include "../graphics/lighting/PointLight.h"
#include "../graphics/graphicscontext.h"
#include "../physics/Collider.h"
#include "../physics/BoxCollider.h"
#include <GLFW/glfw3.h>

int lua_ptreq(lua_State* L) {
    void* a = LuaEngine::getValue<void*>(L, 1);
    void* b = LuaEngine::getValue<void*>(L, 2);

    LuaEngine::pushValue(L, a == b);

    return 1;
}

int entityConstruct0(lua_State* L) {
    Entity* e = new Entity(LuaEngine::getGlobal<Engine*>(L, "engine"));
    LuaEngine::pushValue(L, e);
    LuaEngine::getGlobal<Engine*>(L, "engine")->getWorld()->addEntity(e);
    return 1;
}

int entityConstruct1(lua_State* L) {
    Engine* engine = LuaEngine::getGlobal<Engine*>(L, "engine");
    //if (lua_isstring(L, 1)) {
        Entity* e = new Entity(engine);
        e->addScript(LuaEngine::getValue<const char*>(L, 1));
    /*} else if (lua_isuserdata(L, 1)) {
        e = new Entity(
                LuaEngine::getGlobal<Engine*>(L, "engine"),
                0,
                0,
                LuaEngine::getValue<std::shared_ptr<Renderable>>(L, 1));
    }*/

    LuaEngine::pushValue(L, e);
    LuaEngine::getGlobal<Engine*>(L, "engine")->getWorld()->addEntity(e);
    return 1;
}
/*
int entityConstruct2(lua_State* L) {
    Entity* e = new Entity(
            LuaEngine::getGlobal<Engine*>(L, "engine"),
            LuaEngine::getValue<float>(L, 1),
            LuaEngine::getValue<float>(L, 2));
    LuaEngine::pushValue(L, e);
    LuaEngine::getGlobal<Engine*>(L, "engine")->getWorld()->addEntity(e);
    return 1;
}

int entityConstruct3(lua_State* L) {
    Entity* e;
    if (lua_isstring(L, 1)) {
        e = LuaEngine::getGlobal<Engine*>(L, "engine")->getResourceManager()->loadEntity(LuaEngine::getValue<const char*>(L, 1))->create(
                LuaEngine::getGlobal<Engine*>(L, "engine"),
                LuaEngine::getValue<float>(L, 2),
                LuaEngine::getValue<float>(L, 3));
    } else {
        e = new Entity(
                LuaEngine::getGlobal<Engine*>(L, "engine"),
                LuaEngine::getValue<float>(L, 1),
                LuaEngine::getValue<float>(L, 2),
                LuaEngine::getValue<std::shared_ptr<Renderable>>(L, 3));
    }
    LuaEngine::pushValue(L, e);
    LuaEngine::getGlobal<Engine*>(L, "engine")->getWorld()->addEntity(e);
    return 1;
}*/

template<> const char LuaBindings<Entity*>::name[] = "Entity";
template<> lua_constructor LuaBindings<Entity*>::constructors[] = {
        {0, &entityConstruct0},
        {1, &entityConstruct1},
        //{2, &entityConstruct2},
        //{3, &entityConstruct3},
        {0, 0}
};
template<> luaL_reg LuaBindings<Entity*>::functions[] = {
        {"x", &BindFunction<Entity, float>::ptr<&Entity::getX>},
        {"y", &BindFunction<Entity, float>::ptr<&Entity::getY>},
        {"destroy", &BindFunction<Entity, void>::ptr<&Entity::destroy>},
        {"move", &BindFunction<Entity, void, float, float>::ptr<&Entity::move>},
        {"setX", &BindFunction<Entity, void, float>::ptr<&Entity::setX>},
        {"setY", &BindFunction<Entity, void, float>::ptr<&Entity::setY>},
        {"pos", &BindFunction<Entity, Vector2&>::ptr<&Entity::getPosition>},
        {"setPos", &BindFunction<Entity, void, const Vector2&>::ptr<&Entity::setPosition>},
        {"rotation", &BindFunction<Entity, float>::ptr<&Entity::getRotation>},
        {"setRotation", &BindFunction<Entity, void, float>::ptr<&Entity::setRotation>},
        {"renderable", &BindFunction<Entity, std::shared_ptr<Renderable>>::ptr<&Entity::getRenderable>},
        {"setRenderable", &BindFunction<Entity, void, std::shared_ptr<Renderable>>::ptr<&Entity::setRenderable>},
        {"addScript", &BindFunction<Entity, void, std::string>::ptr<&Entity::addScript>},
        {"getScript", &BindFunction<Entity, ScriptInstance*, std::string>::ptr<&Entity::getScript>},
        {"removeScript", &BindFunction<Entity, ScriptInstance*, std::string>::ptr<&Entity::getScript>},
        {"collider", &BindFunction<Entity, std::shared_ptr<Collider>>::ptr<&Entity::getCollider>},
        {"setCollider", &BindFunction<Entity, void, std::shared_ptr<Collider>>::ptr<&Entity::setCollider>},
        {"__eq", lua_ptreq},
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




int colorconstruct0(lua_State* L) {
    LuaEngine::pushValue(L, Color());
    return 1;
}

int colorconstruct3(lua_State* L) {
    float r = LuaEngine::getValue<float>(L, 1);
    float g = LuaEngine::getValue<float>(L, 2);
    float b = LuaEngine::getValue<float>(L, 3);
    LuaEngine::pushValue(L, Color(r, g, b));
    return 1;
}

template<> const char LuaBindings<Color>::name[] = "Color";
template<> lua_constructor LuaBindings<Color>::constructors[] = {
        {0, &colorconstruct0},
        {3, &colorconstruct3},
        {0, 0}
};
template<> luaL_reg LuaBindings<Color>::functions[] = {
        {"r", &BindFunction<Color, float>::ref<&Color::getR>},
        {"g", &BindFunction<Color, float>::ref<&Color::getG>},
        {"b", &BindFunction<Color, float>::ref<&Color::getB>},
        {"setR", &BindFunction<Color, void, float>::ref<&Color::setR>},
        {"setG", &BindFunction<Color, void, float>::ref<&Color::setG>},
        {"setB", &BindFunction<Color, void, float>::ref<&Color::setB>},
        {"setRGB", &BindFunction<Color, void, float, float, float>::ref<&Color::setRGB>},
        {"__mul", &BindFunction<Color, Color, float>::ref<&Color::operator*>},
        {"__div", &BindFunction<Color, Color, float>::ref<&Color::operator/>},
        {0, 0}
};




template<> const char LuaBindings<Engine*>::name[] = "Engine";
template<> lua_constructor LuaBindings<Engine*>::constructors[] = {
        {0, 0}
};
template<> luaL_reg LuaBindings<Engine*>::functions[] = {
        {"window", &BindFunction<Engine, Window*>::ptr<&Engine::getWindow>},
        {"world", &BindFunction<Engine, World*>::ptr<&Engine::getWorld>},
        {"settings", &BindFunction<Engine, Settings*>::ptr<&Engine::getSettings>},
        {"loadWorld", &BindFunction<Engine, void, std::string>::ptr<&Engine::loadWorld>},
        {0, 0}
};





template<> const char LuaBindings<GraphicsContext*>::name[] = "GraphicsContext";
template<> lua_constructor LuaBindings<GraphicsContext*>::constructors[] = {
        {0, 0}
};
template<> luaL_reg LuaBindings<GraphicsContext*>::functions[] = {
        {"tonemapMaxLum", &BindFunction<GraphicsContext, float>::ptr<&GraphicsContext::getTonemapTargetMaxLum>},
        {"setTonemapMaxLum", &BindFunction<GraphicsContext, void, float>::ptr<&GraphicsContext::setTonemapTargetMaxLum>},
        {"tonemapScale", &BindFunction<GraphicsContext, float>::ptr<&GraphicsContext::getTonemapScale>},
        {"setTonemapScale", &BindFunction<GraphicsContext, void, float>::ptr<&GraphicsContext::setTonemapScale>},
        {0, 0}
};





template<> const char LuaBindings<World*>::name[] = "World";
template<> lua_constructor LuaBindings<World*>::constructors[] = {
        {0, 0}
};
template<> luaL_reg LuaBindings<World*>::functions[] = {
        //{"destroyEntity", &BindFunction<World, void, Entity*>::ptr<&World::destroyEntity>},
        {"entityCount", &BindFunction<World, int>::ptr<&World::getEntityCount>},
        {"entities", &BindFunction<World, LuaIterator<std::list<Entity*>::iterator>>::ptr<&World::getEntitiesIterator>},
        {"lights", &BindFunction<World, LuaIterator<std::vector<std::shared_ptr<Light>>::iterator>>::ptr<&World::getLightsIterator>},
        {"addLight", &BindFunction<World, void, std::shared_ptr<Light>>::ptr<&World::addLight>},
        {"removeLight", &BindFunction<World, void, std::shared_ptr<Light>>::ptr<&World::removeLight>},
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
        {"keyIsUp", &BindFunction<Window, bool, int>::ptr<&Window::keyIsUp>},
        {"keyIsPressed", &BindFunction<Window, bool, int>::ptr<&Window::keyIsPressed>},
        {"keyIsReleased", &BindFunction<Window, bool, int>::ptr<&Window::keyIsReleased>},
        {"buttonIsDown", &BindFunction<Window, bool, int>::ptr<&Window::buttonIsDown>},
        {"buttonIsUp", &BindFunction<Window, bool, int>::ptr<&Window::buttonIsUp>},
        {"buttonIsPressed", &BindFunction<Window, bool, int>::ptr<&Window::buttonIsPressed>},
        {"buttonIsReleased", &BindFunction<Window, bool, int>::ptr<&Window::buttonIsReleased>},
        {0, 0}
};



int spriteConstruct1(lua_State* L) {
    Engine* engine = LuaEngine::getGlobal<Engine*>(L, "engine");
    std::shared_ptr<Sprite> back = std::make_shared<Sprite>(engine, engine->getResourceManager()->loadTexture(LuaEngine::getValue<const char*>(L, 1)));
    LuaEngine::pushValue(L, back);
    return 1;
}



int spriteConstruct2(lua_State* L) {
    Engine* engine = LuaEngine::getGlobal<Engine*>(L, "engine");
    std::shared_ptr<Sprite> back = std::make_shared<Sprite>(engine, engine->getResourceManager()->loadTexture(LuaEngine::getValue<const char*>(L, 1)));
    back->setNormal(engine->getResourceManager()->loadTexture(LuaEngine::getValue<const char*>(L, 2)));
    LuaEngine::pushValue(L, back);
    return 1;
}


template<> const char LuaBindings<std::shared_ptr<Sprite>>::name[] = "Sprite";
template<> lua_constructor LuaBindings<std::shared_ptr<Sprite>>::constructors[] = {
        {1, &spriteConstruct1},
        {2, &spriteConstruct2},
        {0, 0}
};
template<> luaL_reg LuaBindings<std::shared_ptr<Sprite>>::functions[] = {
        {"origin", &BindFunction<Sprite, Vector2>::shared<&Sprite::getOrigin>},
        {"setOrigin", &BindFunction<Sprite, void, const Vector2&>::shared<&Sprite::setOrigin>},
        {"centerOrigin", &BindFunction<Sprite, void>::shared<&Sprite::centerOrigin>},
        {"lit", &BindFunction<Sprite, bool>::shared<&Sprite::getLit>},
        {"setLit", &BindFunction<Sprite, void, bool>::shared<&Sprite::setLit>},
        {"diffuse", &BindFunction<Sprite, std::shared_ptr<GL30Texture>>::shared<&Sprite::getDiffuse>},
        {"normal", &BindFunction<Sprite, std::shared_ptr<GL30Texture>>::shared<&Sprite::getNormal>},
        {"setDiffuse", &BindFunction<Sprite, void, std::shared_ptr<GL30Texture>>::shared<&Sprite::setDiffuse>},
        {"setNormal", &BindFunction<Sprite, void, std::shared_ptr<GL30Texture>>::shared<&Sprite::setNormal>},
        {0, 0}
};


int backgroundConstruct1(lua_State* L) {
    Engine* engine = LuaEngine::getGlobal<Engine*>(L, "engine");
    std::shared_ptr<Background> back = std::make_shared<Background>(engine, engine->getResourceManager()->loadTexture(LuaEngine::getValue<const char*>(L, 1)));
    LuaEngine::pushValue(L, back);
    return 1;
}



int backgroundConstruct2(lua_State* L) {
    Engine* engine = LuaEngine::getGlobal<Engine*>(L, "engine");
    std::shared_ptr<Background> back = std::make_shared<Background>(engine, engine->getResourceManager()->loadTexture(LuaEngine::getValue<const char*>(L, 1)));
    back->setNormal(engine->getResourceManager()->loadTexture(LuaEngine::getValue<const char*>(L, 2)));
    LuaEngine::pushValue(L, back);
    return 1;
}



template<> const char LuaBindings<std::shared_ptr<Background>>::name[] = "Background";
template<> lua_constructor LuaBindings<std::shared_ptr<Background>>::constructors[] = {
        {1, &backgroundConstruct1},
        {2, &backgroundConstruct2},
        {0, 0}
};
template<> luaL_reg LuaBindings<std::shared_ptr<Background>>::functions[] = {
        {"scale",    &BindFunction<Background, float>::shared<&Background::scale>},
        {"setScale", &BindFunction<Background, void, float>::shared<&Background::setScale>},
        {0, 0}
};
/*        void setDiffuse(std::shared_ptr<GL30Texture> texture);
        std::shared_ptr<GL30Texture> getDiffuse() const;

        void setNormal(std::shared_ptr<GL30Texture> texture);
        std::shared_ptr<GL30Texture> getNormal() const;*/

  //      {"setDiffuse", &BindFunction<Sprite, void, std::shared_ptr<GL30Texture>>::shared<&Sprite::setDiffuse>},
  //      {"setNormal", &BindFunction<Sprite, void, std::shared_ptr<GL30Texture>>::shared<&Sprite::setNormal>},




template<> const char LuaBindings<std::shared_ptr<GL30Texture>>::name[] = "GL30Texture";
template<> lua_constructor LuaBindings<std::shared_ptr<GL30Texture>>::constructors[] = {
        {0, 0}
};
template<> luaL_reg LuaBindings<std::shared_ptr<GL30Texture>>::functions[] = {
        {"width", &BindFunction<GL30Texture, int>::shared<&GL30Texture::getWidth>},
        {"height", &BindFunction<GL30Texture, int>::shared<&GL30Texture::getHeight>},
        {"channels", &BindFunction<GL30Texture, int>::shared<&GL30Texture::getChannels>},
        {0, 0}
};





int plconstruct0(lua_State* L) {
    std::shared_ptr<PointLight> pl = std::make_shared<PointLight>(LuaEngine::getGlobal<Engine*>(L, "engine"), Color(), Vector2(), 0, 0, 0);
    LuaEngine::pushValue(L, pl);
    return 1;
}

int plconstruct5(lua_State* L) {
    std::shared_ptr<PointLight> pl = std::make_shared<PointLight>(
            LuaEngine::getGlobal<Engine*>(L, "engine"),
            LuaEngine::getValue<Color>(L, 1),
            LuaEngine::getValue<Vector2>(L, 2),
            LuaEngine::getValue<float>(L, 3),
            LuaEngine::getValue<float>(L, 4),
            LuaEngine::getValue<float>(L, 5));

    LuaEngine::pushValue(L, pl);
    return 1;
}

template<> const char LuaBindings<std::shared_ptr<PointLight>>::name[] = "PointLight";
template<> lua_constructor LuaBindings<std::shared_ptr<PointLight>>::constructors[] = {
        {0, plconstruct0},
        {5, plconstruct5},
        {0, 0}
};
template<> luaL_reg LuaBindings<std::shared_ptr<PointLight>>::functions[] = {
        {"color", &BindFunction<PointLight, Color&>::shared<&PointLight::getColor>},
        {"pos", &BindFunction<PointLight, Vector2&>::shared<&PointLight::getPosition>},
        {"depth", &BindFunction<PointLight, float>::shared<&PointLight::getDepth>},
        {"drop", &BindFunction<PointLight, float>::shared<&PointLight::getDrop>},
        {"end", &BindFunction<PointLight, float>::shared<&PointLight::getEnd>},
        {"setColor", &BindFunction<PointLight, void, Color>::shared<&PointLight::setColor>},
        {"setPos", &BindFunction<PointLight, void, Vector2>::shared<&PointLight::setPosition>},
        {"setDepth", &BindFunction<PointLight, void, float>::shared<&PointLight::setDepth>},
        {"setDrop", &BindFunction<PointLight, void, float>::shared<&PointLight::setDrop>},
        {"setEnd", &BindFunction<PointLight, void, float>::shared<&PointLight::setEnd>},
        {0, 0}
};





int ambientConstruct0(lua_State* L) {
    std::shared_ptr<AmbientLight> pl = std::make_shared<AmbientLight>(LuaEngine::getGlobal<Engine*>(L, "engine"), Color());
    LuaEngine::pushValue(L, pl);
    return 1;
}

int ambientConstruct1(lua_State* L) {
    std::shared_ptr<AmbientLight> pl = std::make_shared<AmbientLight>(LuaEngine::getGlobal<Engine*>(L, "engine"), LuaEngine::getValue<Color>(L, 1));
    LuaEngine::pushValue(L, pl);
    return 1;
}

template<> const char LuaBindings<std::shared_ptr<AmbientLight>>::name[] = "AmbientLight";
template<> lua_constructor LuaBindings<std::shared_ptr<AmbientLight>>::constructors[] = {
        {0, ambientConstruct0},
        {1, ambientConstruct1},
        {0, 0}
};

template<> luaL_reg LuaBindings<std::shared_ptr<AmbientLight>>::functions[] = {
        {"color", &BindFunction<AmbientLight, Color&>::shared<&AmbientLight::getColor>},
        {"setColor", &BindFunction<AmbientLight, void, const Color&>::shared<&AmbientLight::setColor>},
        {0, 0}
};



int BoxColliderConstruct2(lua_State* L) {
    std::shared_ptr<BoxCollider> pl = std::make_shared<BoxCollider>(LuaEngine::getValue<float>(L, 1), LuaEngine::getValue<float>(L, 2));
    LuaEngine::pushValue(L, pl);
    return 1;
}

template<> const char LuaBindings<std::shared_ptr<BoxCollider>>::name[] = "BoxCollider";
template<> lua_constructor LuaBindings<std::shared_ptr<BoxCollider>>::constructors[] = {
        {2, BoxColliderConstruct2},
        {0, 0}
};

template<> luaL_reg LuaBindings<std::shared_ptr<BoxCollider>>::functions[] = {
        {"width", &BindFunction<BoxCollider, float>::shared<&BoxCollider::getWidth>},
        {"height", &BindFunction<BoxCollider, float>::shared<&BoxCollider::getHeight>},
        {"setWidth", &BindFunction<BoxCollider, void, float>::shared<&BoxCollider::setWidth>},
        {"setHeight", &BindFunction<BoxCollider, void, float>::shared<&BoxCollider::setHeight>},
        {"origin", &BindFunction<BoxCollider, Vector2>::shared<&BoxCollider::getOrigin>},
        {"setOrigin", &BindFunction<BoxCollider, void, const Vector2&>::shared<&BoxCollider::setOrigin>},
        {"centerOrigin", &BindFunction<BoxCollider, void>::shared<&BoxCollider::centerOrigin>},
        {0, 0}
};



template<> const char LuaBindings<ScriptInstance*>::name[] = "ScriptInstance";
template<> lua_constructor LuaBindings<ScriptInstance*>::constructors[] = {
        {0, 0}
};
template<> luaL_reg LuaBindings<ScriptInstance*>::functions[] = {
        {"lua", ScriptInstance::lua},
        {0, 0}
};




template<class T>
struct LuaBindings<LuaIterator<T>> {
    static const char name[];
    static lua_constructor constructors[];
    static luaL_reg functions[];
};

template<> const char LuaBindings<LuaIterator<std::vector<std::shared_ptr<Light>>::iterator>>::name[] = "Iterator<Entity>";
template<> const char LuaBindings<LuaIterator<std::list<Entity*>::iterator>>::name[] = "Iterator<Light>";
template<class T> lua_constructor LuaBindings<LuaIterator<T>>::constructors[] = {
        {0, 0}
};
template<class T> luaL_reg LuaBindings<LuaIterator<T>>::functions[] = {
        {"next", LuaIterator<T>::lua_next},
        {"value", LuaIterator<T>::lua_value},
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
        {"left", GLFW_MOUSE_BUTTON_LEFT},
        {"right", GLFW_MOUSE_BUTTON_RIGHT},
        {"middle", GLFW_MOUSE_BUTTON_MIDDLE},
        {0, 0}
};

void bind(LuaEngine* engine, lua_State* L) {
    engine->registerClass<Vector2>();
    engine->registerClass<Color>();
    engine->registerClass<Entity*>();
    engine->registerClass<Engine*>();
    engine->registerClass<World*>();
    engine->registerClass<Window*>();
    engine->registerClass<ScriptInstance*>();
    engine->registerClass<GraphicsContext*>();
    engine->registerClass<std::shared_ptr<GL30Texture>>();
    engine->registerClass<std::shared_ptr<Sprite>>();
    engine->registerClass<std::shared_ptr<Background>>();
    engine->registerClass<std::shared_ptr<PointLight>>();
    engine->registerClass<std::shared_ptr<AmbientLight>>();
    engine->registerClass<std::shared_ptr<BoxCollider>>();
    engine->registerClass<LuaIterator<std::list<Entity*>::iterator>>();
    engine->registerClass<LuaIterator<std::vector<std::shared_ptr<Light>>::iterator>>();

    engine->registerEnum("Keys", Keys);
    engine->registerEnum("Buttons", Buttons);
}