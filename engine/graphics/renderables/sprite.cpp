#include "sprite.h"
#include "../../resources/ResourceManager.h"
#include <glad/glad.h>

Sprite::Sprite(Engine* engine, const std::shared_ptr<GL30Texture>& diffuse)
		: Renderable(engine), _diffuse(diffuse), _normal(_engine->getResourceManager()->loadTexture("res/assets/default_normal.png")), _origin(0, 0), _isLit(true)
{
	setProgram(_engine->getResourceManager()->loadProgram("res/shaders/spriteEffect.vsh", "res/shaders/spriteEffect.fsh"));
}

Sprite::~Sprite()
{
}

void Sprite::setDiffuse(std::shared_ptr<GL30Texture> texture) {
	_diffuse = texture;
}

std::shared_ptr<GL30Texture> Sprite::getDiffuse() const {
	return _diffuse;
}
	
void Sprite::setNormal(std::shared_ptr<GL30Texture> texture) {
	_normal = texture;
}

std::shared_ptr<GL30Texture> Sprite::getNormal() const {
	return _normal;
}

bool Sprite::getLit() const {
	return _isLit;
}

void Sprite::setLit(bool isLit) {
	_isLit = isLit;
}

void Sprite::centerOrigin() {
	_origin.setX(_diffuse->getWidth() / 2);
	_origin.setY(_diffuse->getHeight() / 2);
}
Vector2 Sprite::getOrigin() const {
	return _origin;
}

void Sprite::setOrigin(const Vector2& v) {
	_origin = v;
}

void Sprite::enableForRender() {
	getProgram()->enableProgram();
	glUniform1i(glGetUniformLocation(getProgram()->getProgramID(), "diffuse"), 0);
	glUniform1i(glGetUniformLocation(getProgram()->getProgramID(), "normal"), 1);
	//always enable the diffuse map
	_diffuse->enableTexture(0);
	
	//if we have a normal map, enable it too.
	if (_normal.get() != nullptr)
		_normal->enableTexture(1);
		
	glUniform2f(glGetUniformLocation(getProgram()->getProgramID(), "origin"), _origin.getX(), _origin.getY());
	glUniform2f(glGetUniformLocation(getProgram()->getProgramID(), "size"), _diffuse->getWidth(), _diffuse->getHeight());
	glUniform1f(glGetUniformLocation(getProgram()->getProgramID(), "brightness"), _isLit? 1 : 0);	
}

void Sprite::push(lua_State* L, Renderable* ptr) {
    LuaEngine::rawPushValue<Sprite*>(L, static_cast<Sprite*>(ptr));
}

void Sprite::push(lua_State* L, std::shared_ptr<Renderable> ptr) {
    LuaEngine::rawPushValue<std::shared_ptr<Sprite>>(L, std::static_pointer_cast<Sprite>(ptr));
}
