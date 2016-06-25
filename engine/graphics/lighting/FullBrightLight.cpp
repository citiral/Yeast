#include "FullBrightLight.h"
#include <glad/glad.h>
#include "../../resourceloader.h"

FullBrightLight::FullBrightLight(Engine* engine): Light(engine)
{
    setProgram(_engine->getResourceLoader()->loadProgram("res/shaders/lighting/vertex.vsh", "res/shaders/lighting/fullbright.fsh"));
}

FullBrightLight::~FullBrightLight()
{
}

void FullBrightLight::enableForRender() {
    getProgram()->enableProgram();
}