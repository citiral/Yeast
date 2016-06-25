#include "Entity.h"
#include "graphics/renderables/renderable.h"
#include "physics/Collider.h"
#include "graphics/graphicscontext.h"


Entity::Entity(Engine* engine, float x, float y, Renderable* renderable) : _position(x, y), _type("") {
    _engine = engine;
    _renderable = nullptr;
	_collider = nullptr;
	_rotation = 0;
    _state = EntityState::INVALID;
}

Entity::~Entity() {
    if (_renderable != nullptr) {
        delete _renderable;
    } if (_collider != nullptr) {
		delete _collider;
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

void Entity::setPosition(float x, float y) {
	setX(x);
	setY(y);
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

void Entity::setRenderable(Renderable *r) {
    if (_renderable != nullptr)
        delete _renderable;
    _renderable = r;
}

Renderable *Entity::getRenderable() const {
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
		for (std::shared_ptr<Entity> other : _engine->getWorld()->getEntities())
		{
			if (other.get() == this) continue;
			if (other->_collider != nullptr)
			{
				if (_collider->collidesWith(*(other->_collider)))
				{
					onCollide(other.get());
					_collider->resolveCollision(*(other->_collider),
						std::bind(&Entity::onMoveCollideX, this, other.get(), std::placeholders::_1),
						std::bind(&Entity::onMoveCollideY, this, other.get(), std::placeholders::_1)
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
