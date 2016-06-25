#include "PlayerEntity.h"
#include "bullet.h"
#include "gunshot.h"
#include "../../engine/resourceloader.h"
#include "../../engine/graphics/renderables/colorfield.h"
#include "../../engine/graphics/renderables/sprite.h"
#include "../../engine/graphics/renderables/Background.h"
#include "../../engine/physics/BoxCollider.h"
#include "../../engine/windowing/window.h"
#include <iostream>
#include <cmath>
#include <windowing/keys.h>

PlayerEntity::PlayerEntity(Engine* engine, float y): Entity(engine)
{
	setType("player");
	setY(y);
	
	_XmaxSpeed = 300;
	_YmaxSpeed = 300;
	
	_Xspeed = 0;
	_Yspeed = 0;
	
	_shootCooldown = 0;
		
	setCollider(new BoxCollider(20,20));
}

PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::onMoveCollideX(Entity* e, float amount)
{
	if (e->getType() == "alien")
		getWorld()->removeEntity(this);
	setX(getX() + amount);
}

void PlayerEntity::onMoveCollideY(Entity* e, float amount)
{
	if (e->getType() == "alien")
		getWorld()->removeEntity(this);
	setY(getY() + amount);
}

void PlayerEntity::added()
{
	//setRenderable(new GL30Texture("res/assets/player.png"));
	//setRenderable(new ColorField(Color(0.3,0.5,0.8), Vector2(15, 25)));
	setRenderable(new Sprite(getEngine(), getEngine()->getResourceLoader()->loadTexture("res/assets/ball_diffuse.png")));
	((Sprite*)getRenderable())->setNormal(getEngine()->getResourceLoader()->loadTexture("res/assets/ball_normal.png"));
	((Sprite*)getRenderable())->centerOrigin();
	std::cout << "I'm the player! LOL";
}

void PlayerEntity::removed()
{
}

void PlayerEntity::update(float dt)
{
	_Xspeed = 0;
	_Yspeed = 0;
	
	_shootCooldown -= dt;
	

	
	//X SPEED
	if (WINDOW->keyIsDown(KEY_LEFT)) {
		_Xspeed = -_XmaxSpeed;
	}
	if (WINDOW->keyIsDown(KEY_RIGHT)) {
		_Xspeed = _XmaxSpeed;
	}
	if (WINDOW->keyIsDown(KEY_UP)) {
		_Yspeed = _YmaxSpeed;
	}
	if (WINDOW->keyIsDown(KEY_DOWN)) {
		_Yspeed = -_YmaxSpeed;
	}
		
	moveTo(getX() + _Xspeed * dt, getY() + _Yspeed * dt);
	
	float angle = std::atan2(WINDOW->getMouseY() - getY(), WINDOW->getMouseX() - getX());
	setRotation(-angle);
	
	if (WINDOW->buttonIsDown(0) && _shootCooldown <= 0) {
		_shootCooldown = 0.6;
		Vector2 gunfront(50, 0);
		gunfront = gunfront.rotate(angle);
		getWorld()->addEntity(new Gunshot(getEngine(), getPosition() + gunfront));
		getWorld()->addEntity(new Bullet(getEngine(), getPosition() + gunfront, getRotation()));
	}
}
