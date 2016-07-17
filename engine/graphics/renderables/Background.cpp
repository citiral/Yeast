#include "Background.h"
#include "../../resources/ResourceManager.h"
#include <glad/glad.h>

Background::Background(Engine* engine, const Resource<GL30Texture>& diffuse, float scale)
		: Renderable(engine), _diffuse(diffuse), _normal(_engine->getResourceManager()->loadTexture("res/assets/default_normal.png"))
{
	setProgram(_engine->getResourceManager()->loadProgram("res/shaders/backgroundEffect.vsh", "res/shaders/backgroundEffect.fsh"));
	_diffuse->setRepeat(GL_REPEAT);
	_scale = scale;
}

Background::~Background()
{
}

void Background::setDiffuse(Resource<GL30Texture> texture) {
	_diffuse = texture;
}

Resource<GL30Texture> Background::getDiffuse() const {
	return _diffuse;
}
	
void Background::setNormal(Resource<GL30Texture> texture) {
	_normal = texture;
}

Resource<GL30Texture> Background::getNormal() const {
	return _normal;
}

void Background::enableForRender() {
	getProgram()->enableProgram();
	glUniform1i(glGetUniformLocation(getProgram()->getProgramID(), "diffuse"), 0);
	glUniform1i(glGetUniformLocation(getProgram()->getProgramID(), "normal"), 1);
	
	//always enable the diffuse map
	_diffuse->enableTexture(0);
	
	//if we have a normal map, enable it too.
	if (_normal.getResource() != nullptr) {
		_normal->enableTexture(1);
	}
	
	glUniform2f(glGetUniformLocation(getProgram()->getProgramID(), "size"), _diffuse->getWidth() * _scale, _diffuse->getHeight() * _scale);
}

void Background::push(lua_State* L, void* ptr) {
    LuaEngine::rawPushValue<Background*>(L, (Background*)ptr);
}
