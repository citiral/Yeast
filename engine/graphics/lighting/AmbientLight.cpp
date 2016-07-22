#include "AmbientLight.h"
#include "../../resources/ResourceManager.h"
#include <glad/glad.h>

AmbientLight::AmbientLight(Engine* engine, const Color& color) : Light(engine), _lightColor(color)
{
	setProgram(_engine->getResourceManager()->loadProgram("res/shaders/lighting/vertex.vsh", "res/shaders/lighting/ambient.fsh"));
}

AmbientLight::~AmbientLight()
{
}

void AmbientLight::enableForRender() {
	getProgram()->enableProgram();
	glUniform3f(glGetUniformLocation(getProgram()->getProgramID(), "light.color"), _lightColor.getR(), _lightColor.getG(), _lightColor.getB());
}

Color AmbientLight::getColor() const {
	return _lightColor;
}

void AmbientLight::setColor(const Color& c) {
	_lightColor = c;
}

void AmbientLight::push(lua_State* L, Light* ptr) {
	LuaEngine::rawPushValue<AmbientLight*>(L, static_cast<AmbientLight*>(ptr));
}

void AmbientLight::push(lua_State* L, std::shared_ptr<Light> ptr) {
	LuaEngine::rawPushValue<std::shared_ptr<AmbientLight>>(L, std::static_pointer_cast<AmbientLight>(ptr));
}