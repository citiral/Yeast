#include "Alien.h"
#include <cmath>
#include "../../engine/graphics/renderables/sprite.h"
#include "../../engine/physics/BoxCollider.h"
#include "../../engine/resourceloader.h"

Alien::Alien(Engine* engine, Entity* target, const Vector2& pos) : Entity(engine), _target(target)
{
	setType("alien");
	setPosition(pos);
}

Alien::~Alien()
{
}

void Alien::added() {
	Sprite* sprite = new Sprite(getEngine(), getEngine()->getResourceLoader()->loadTexture("res/assets/monster.png"));
	sprite->setNormal(getEngine()->getResourceLoader()->loadTexture("res/assets/monster_normal.png"));
	sprite->centerOrigin();
	setRenderable(sprite);
	setCollider(new BoxCollider(100, 100));
	((BoxCollider*)getCollider())->centerOrigin();
}

void Alien::removed() {
	
}

void Alien::update(float dt) {
	float direction = std::atan2(getY() - _target->getY(), _target->getX() - getX());
	
	float xspeed = cos(direction) * 150;
	float yspeed = sin(direction) * 150;
	
	setRotation(direction);
	
	moveTo(getX() + xspeed * dt, getY() - yspeed * dt);
}