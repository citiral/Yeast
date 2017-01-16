#include "Background.h"
#include "../../resources/ResourceManager.h"
#include <glad/glad.h>

Background::Background(Engine* engine, const std::shared_ptr<GL30Texture>& diffuse, float scale)
		: Renderable(engine), _diffuse(diffuse), _normal(_engine->getResourceManager()->loadTexture("default_normal.png"))
{
	setProgram(_engine->getResourceManager()->loadProgram("backgroundEffect.vsh", "backgroundEffect.fsh"));
	_diffuse->setRepeat(GL_REPEAT);
	_scale = scale;
}

Background::~Background()
{
}

void Background::setDiffuse(std::shared_ptr<GL30Texture> texture) {
	_diffuse = texture;
}

std::shared_ptr<GL30Texture> Background::getDiffuse() const {
	return _diffuse;
}
	
void Background::setNormal(std::shared_ptr<GL30Texture> texture) {
	_normal = texture;
}

std::shared_ptr<GL30Texture> Background::getNormal() const {
	return _normal;
}

void Background::enableForRender() {
	getProgram()->enableProgram();
	glUniform1i(glGetUniformLocation(getProgram()->getProgramID(), "diffuse"), 0);
	glUniform1i(glGetUniformLocation(getProgram()->getProgramID(), "normal"), 1);
	
	//always enable the diffuse map
	_diffuse->enableTexture(0);
	
	//if we have a normal map, enable it too.
	if (_normal.get() != nullptr) {
		_normal->enableTexture(1);
	}
	
	glUniform2f(glGetUniformLocation(getProgram()->getProgramID(), "size"), _diffuse->getWidth() * _scale, _diffuse->getHeight() * _scale);
}

void Background::push(lua_State* L, Renderable* ptr) {
    LuaEngine::rawPushValue<Background*>(L, static_cast<Background*>(ptr));
}

void Background::push(lua_State* L, std::shared_ptr<Renderable> ptr) {
    LuaEngine::rawPushValue<std::shared_ptr<Background>>(L, std::static_pointer_cast<Background>(ptr));
}

float Background::scale() const {
	return _scale;
}

void Background::setScale(float scale) {
	_scale = scale;
}