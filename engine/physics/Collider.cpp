#include "Collider.h"
#include <cmath>


Collider::Collider()
{
	_colliderType = ColliderType::NONE;
}

Collider::~Collider()
{
}


bool Collider::couldCollideWith(const Collider& other) const {
	return	getX() < other.getX() + other.getBoundingWidth() && getX() + getBoundingWidth() > other.getX() &&
			getY() < other.getY() + other.getBoundingHeight() && getY() + getBoundingHeight() > other.getY();
}

const Vector2& Collider::getPos() const {
	return _pos;
}

float Collider::getX() const {
	return _pos.getX();
}

float Collider::getY() const {
	return _pos.getY();
}

void Collider::setPos(const Vector2& pos) {
	_pos = pos;
}

void Collider::setX(float x) {
	_pos.setX(x);
}

void Collider::setY(float y) {
	_pos.setY(y);
}
	
bool Collider::isStatic() const {
	return _static;
}

void Collider::setStatic(bool s) {
	_static = s;
}

ColliderType Collider::getColliderType() const {
	return _colliderType;
}
