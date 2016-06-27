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