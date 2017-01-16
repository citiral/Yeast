#include "Entity.h"
#include "graphics/renderables/renderable.h"
#include "physics/Collider.h"
#include "graphics/graphicscontext.h"
#include "resources/ResourceManager.h"
#include "paths.h"


Entity::Entity(Engine* engine) {
    _engine = engine;
    _renderable = nullptr;
	_collider = nullptr;
	_rotation = 0;
    _state = EntityState::INVALID;
}

Entity::~Entity() {
    if (_collider != nullptr) {
		delete _collider;
	}

    // clean up the scripts
    for (auto it = _scripts.begin(); it != _scripts.end() ; ++it) {
        delete (*it).second;
    }
}

World *Entity::getWorld() {
    return _engine->getWorld();
}

Engine* Entity::getEngine() {
    return _engine;
}

float Entity::getX() const {
    return _position.getX();
}

float Entity::getY() const {
    return _position.getY();
}

void Entity::setX(float x) {
    _position.setX(x);
	if (_collider != nullptr)
		_collider->setX(_position.getX());
}

void Entity::setY(float y) {
    _position.setY(y);
	if (_collider != nullptr)
		_collider->setY(_position.getY());
}

float Entity::getRotation() const {
	return _rotation;
}

void Entity::setRotation(float rotation) {
	_rotation = rotation;
}

Vector2& Entity::getPosition() {
	return _position;
}

void Entity::setPosition(const Vector2& vec) {
	_position = vec;
}

const std::string& Entity::getType() const {
	return _type;
}

void Entity::setType(const std::string& t) {
	_type = t;
}

void Entity::render(GraphicsContext& gc) {
    if (_renderable != nullptr)
        gc.drawRenderable(*_renderable, _position, _rotation, Vector2(1, 1));
}

void Entity::setRenderable(std::shared_ptr<Renderable> r) {
    _renderable = r;
}

std::shared_ptr<Renderable> Entity::getRenderable() const {
    return _renderable;
}

void Entity::setCollider(Collider* r) {
	if (_collider != nullptr)
		delete _collider;
	_collider = r;
	_collider->setX(_position.getX());
	_collider->setY(_position.getY());
}

Collider* Entity::getCollider() const {
	return _collider;
}

void Entity::onCollide(Entity* e) {

}

void Entity::onMoveCollideX(Entity* e, float amount) {

}

void Entity::onMoveCollideY(Entity* e, float amount) {

}
void Entity::moveTo(float x, float y) {
	setX(x);
	setY(y);

	if (_collider != nullptr)
	{
		for (Entity* other : _engine->getWorld()->getEntities())
		{
			if (other == this) continue;
			if (other->_collider != nullptr)
			{
				if (_collider->collidesWith(*(other->_collider)))
				{
					onCollide(other);
					_collider->resolveCollision(*(other->_collider),
						std::bind(&Entity::onMoveCollideX, this, other, std::placeholders::_1),
						std::bind(&Entity::onMoveCollideY, this, other, std::placeholders::_1)
						);
				}
			}
		}
	}
}

void Entity::setState(EntityState state) {
    _state = state;
}

EntityState Entity::getState() const {
    return _state;
}

void Entity::added() {
    for (auto it = _scripts.begin(); it != _scripts.end() ; ++it) {
        (*it).second->runFunction("added");
    }
}

void Entity::destroyed() {
    for (auto it = _scripts.begin(); it != _scripts.end() ; ++it) {
        (*it).second->runFunction("destroyed");
    }
}

void Entity::update(float dt) {
    for (auto it = _scripts.begin(); it != _scripts.end() ; ++it) {
        (*it).second->runFunction("update");
    }
}

void Entity::addScript(std::string name) {
    ScriptInstance* instance = _engine->getResourceManager()->loadScript(FOLDER_SCRIPTS + name)->createInstance(_engine);
    _scripts[name] = instance;

    // register the correct members
    instance->setValue("this", this);

    if (_state == EntityState::ACTIVE) {
        instance->runFunction("added");
    }
}

ScriptInstance* Entity::getScript(std::string name) {
    auto val = _scripts.find(name);

    if (val != _scripts.end()) {
        return (*val).second;
    } else {
        return nullptr;
    }
}

void Entity::removeScript(std::string name) {
    auto val = _scripts.find(name);

    if (val != _scripts.end()) {
        (*val).second->runFunction("destroyed");
        _scripts.erase(name);
    }
}

std::map<std::string, ScriptInstance*>& Entity::getScripts() {
    return _scripts;
}

void Entity::destroy() {
    _engine->getWorld()->destroyEntity(this);
}








