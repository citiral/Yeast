#include "FullBrightLight.h"
#include <glad/glad.h>
#include "../../resources/ResourceManager.h"

FullBrightLight::FullBrightLight(Engine* engine): Light(engine)
{
    setProgram(_engine->getResourceManager()->loadProgram("res/shaders/lighting/vertex.vsh", "res/shaders/lighting/fullbright.fsh"));
}

FullBrightLight::~FullBrightLight()
{
}

void FullBrightLight::enableForRender() {
    getProgram()->enableProgram();
}

void FullBrightLight::push(lua_State* L, Light* ptr) {
    LuaEngine::rawPushValue<FullBrightLight*>(L, static_cast<FullBrightLight*>(ptr));
}

void FullBrightLight::push(lua_State* L, std::shared_ptr<Light> ptr) {
    LuaEngine::rawPushValue<std::shared_ptr<FullBrightLight>>(L, std::static_pointer_cast<FullBrightLight>(ptr));
}