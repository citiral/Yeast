#include "PointLight.h"
#include <glad/glad.h>
#include "../../resources/ResourceManager.h"

PointLight::PointLight(Engine* engine, const Color& color, const Vector2& position, float depth, float drop, float end) :
        Light(engine), _lightColor(color), _position(position), _drop(drop), _end(end), _depth(depth)
{
    setProgram(_engine->getResourceManager()->loadProgram("res/shaders/lighting/point.vsh", "res/shaders/lighting/point.fsh"));
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

float PointLight::getDepth() const {
    return _depth;
}

void PointLight::setDepth(float depth) {
    _depth = depth;
}

void PointLight::enableForRender() {
    getProgram()->enableProgram();

    glUniform3f(getProgram()->getUniform("light.color"), _lightColor.getR(), _lightColor.getG(), _lightColor.getB());
    glUniform2f(getProgram()->getUniform("light.position"), _position.getX(), _position.getY());
    glUniform1f(getProgram()->getUniform("light.drop"), _drop);
    glUniform1f(getProgram()->getUniform("light.end"), _end);
    glUniform1f(getProgram()->getUniform("light.depth"), _depth);
}

void PointLight::push(lua_State* L, Light* ptr) {
    LuaEngine::rawPushValue<PointLight*>(L, static_cast<PointLight*>(ptr));
}

void PointLight::push(lua_State* L, std::shared_ptr<Light> ptr) {
    LuaEngine::rawPushValue<std::shared_ptr<PointLight>>(L, std::static_pointer_cast<PointLight>(ptr));
}

