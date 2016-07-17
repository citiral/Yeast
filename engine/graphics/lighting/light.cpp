#include "light.h"

Light::Light(Engine* engine) : _engine(engine), _program()
{

}

Light::~Light()
{
}

std::shared_ptr<Program> Light::getProgram() const {
    return _program;
}

void Light::setProgram(std::shared_ptr<Program> p) {
    _program = p;
}