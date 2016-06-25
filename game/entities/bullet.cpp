#include "bullet.h"
#include <cmath>
#include "../../engine/resourceloader.h"
#include "../../engine/graphics/renderables/sprite.h"
#include "../../engine/physics/BoxCollider.h"

Bullet::Bullet(Engine* engine, const Vector2& pos, float angle): Entity(engine)
{
	setType("bullet");
	setPosition(pos);
	setRotation(angle);
}

Bullet::~Bullet()
{
}

void Bullet::added()
{
	Sprite* sprite = new Sprite(getEngine(), getEngine()->getResourceLoader()->loadTexture("res/assets/bullet.png"));
	sprite->centerOrigin();
	setRenderable(sprite);
	setCollider(new BoxCollider(5, 5));
	((BoxCollider*)getCollider())->centerOrigin();
}

void Bullet::removed()
{
	
}

void Bullet::update(float dt)
{
	float xspeed = std::cos(getRotation()) * 1500;
	float yspeed = std::sin(getRotation()) * 1500;
	
	moveTo(getX() + xspeed * dt,getY() - yspeed * dt);
}

void Bullet::onCollide(Entity* e) {
	if (e->getType() == "alien") {
		getWorld()->removeEntity(e);
	}
	getWorld()->removeEntity(this);
}