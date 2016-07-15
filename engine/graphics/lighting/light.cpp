#include "light.h"

Light::Light(Engine* engine) : _engine(engine), _program()
{

}

Light::~Light()
{
}

Resource<Program> Light::getProgram() const {
    return _program;
}

void Light::setProgram(Resource<Program> p) {
    _program = p;
}