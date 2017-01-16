#include "BoxCollider.h"

#include "solvers/BoxBoxSolver.h"
#include "../scripting/LuaEngine.h"

BoxCollider::BoxCollider(float width, float height) : _origin(0, 0)
{
	_width = width;
	_height = height;
	_colliderType = ColliderType::BOX;
}

BoxCollider::~BoxCollider()
{
}

float BoxCollider::getHeight() const
{
	return _height;
}

float BoxCollider::getWidth() const
{
	return _width;
}

void BoxCollider::setHeight(float height)
{
	_height = height;
}

void BoxCollider::setWidth(float width)
{
	_width = width;
}

float BoxCollider::getBoundingHeight() const
{
	return _height;
}

float BoxCollider::getBoundingWidth() const
{
	return _width;
}

Vector2 BoxCollider::getOrigin() const {
	return _origin;
}

void BoxCollider::setOrigin(const Vector2& v) {
	_origin = v;
}
	
void BoxCollider::centerOrigin() {
	_origin.setX(_width/2);
	_origin.setY(_height/2);
}

bool BoxCollider::collidesWith(const Collider& other) const
{
	switch (other.getColliderType()) {
		case ColliderType::BOX:
			return BoxBoxSolver::collides(*this, (BoxCollider&)other);
			break;
		case ColliderType::NONE:
		default:
			return false;
			break;
	}
}

void BoxCollider::resolveCollision(const Collider& other, std::function<void(float)> xCallback, std::function<void(float)> yCallback)
{
	switch (other.getColliderType()) {
		case ColliderType::BOX:
			return BoxBoxSolver::resolveCollision(*this, (BoxCollider&)other, xCallback, yCallback);
			break;
		case ColliderType::NONE:
		default:
			return;
			break;
	}
}

void BoxCollider::push(lua_State* L, Collider* ptr) {
	LuaEngine::rawPushValue<BoxCollider*>(L, static_cast<BoxCollider*>(ptr));
}

void BoxCollider::push(lua_State* L, std::shared_ptr<Collider> ptr) {
	LuaEngine::rawPushValue<std::shared_ptr<BoxCollider>>(L, std::static_pointer_cast<BoxCollider>(ptr));
}