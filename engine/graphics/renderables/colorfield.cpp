#include "colorfield.h"
#include <iostream>
#include <glad/glad.h>
#include "../../resources/ResourceManager.h"

ColorField::ColorField(Engine* engine, const Color& color, Vector2 size):
    Renderable(engine) {
	_color = color;
	_size = size;
	setProgram(_engine->getResourceManager()->loadProgram("res/shaders/colorEffect.vsh", "res/shaders/colorEffect.fsh"));
}

ColorField::~ColorField() {
	
}

void ColorField::enableForRender() {
	getProgram()->enableProgram();
   glUniform3f(glGetUniformLocation(getProgram()->getProgramID(), "color"), _color.getR(), _color.getG(), _color.getB());
   glUniform2f(glGetUniformLocation(getProgram()->getProgramID(), "size"), _size.getX(), _size.getY());
}

Color& ColorField::getColor() {
	return _color;
}

Vector2& ColorField::getSize() {
	return _size;
}

void ColorField::push(lua_State* L, void* ptr) {
    LuaEngine::rawPushValue<ColorField*>(L, (ColorField*)ptr);
}
