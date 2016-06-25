#include "PointLight.h"
#include <glad/glad.h>
#include "../../resourceloader.h"

PointLight::PointLight(Engine* engine, const Color& color, const Vector2& position, float depth, float drop, float end) :
        Light(engine), _lightColor(color), _position(position), _depth(depth), _drop(drop), _end(end)
{
    setProgram(_engine->getResourceLoader()->loadProgram("res/shaders/lighting/vertex.vsh", "res/shaders/lighting/point.fsh"));
}

PointLight::~PointLight()
{
}

Color& PointLight::getColor() {
    return _lightColor;
}
void PointLight::setColor(Color c) {
    _lightColor = c;
}

Vector2& PointLight::getPosition() {
    return _position;
}
void PointLight::setPosition(Vector2 p) {
    _position = p;
}

float PointLight::getDrop() const {
    return _drop;
}

void PointLight::setDrop(float drop) {
    _drop = drop;
}

float PointLight::getEnd() const {
    return _end;
}
void PointLight::setEnd(float end) {
    _end = end;
}

void PointLight::enableForRender() {
    getProgram()->enableProgram();

    glUniform3f(glGetUniformLocation(getProgram()->getProgramID(), "light.color"), _lightColor.getR(), _lightColor.getG(), _lightColor.getB());
    glUniform2f(glGetUniformLocation(getProgram()->getProgramID(), "light.position"), _position.getX(), _position.getY());
    glUniform1f(glGetUniformLocation(getProgram()->getProgramID(), "light.drop"), _drop);
    glUniform1f(glGetUniformLocation(getProgram()->getProgramID(), "light.end"), _end);
    glUniform1f(glGetUniformLocation(getProgram()->getProgramID(), "light.depth"), _depth);
}