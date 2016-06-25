#include "AmbientLight.h"
#include "../../resourceloader.h"
#include <glad/glad.h>

AmbientLight::AmbientLight(Engine* engine, const Color& color) : Light(engine), _lightColor(color)
{
	setProgram(_engine->getResourceLoader()->loadProgram("res/shaders/lighting/vertex.vsh", "res/shaders/lighting/ambient.fsh"));
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