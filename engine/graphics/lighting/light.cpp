#include "light.h"

Light::Light(Engine* engine) : _program(), _engine(engine)
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