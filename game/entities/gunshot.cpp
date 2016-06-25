#include "gunshot.h"
#include <iostream>

Gunshot::Gunshot(Engine* engine, const Vector2& pos): Entity(engine)
{
	setPosition(pos);
}

Gunshot::~Gunshot()
{
}


void Gunshot::added() {
	_elapsed = 0;
	_light = new PointLight(getEngine(), Color(252/255.0, 238/255.0, 128/255.0) * 20, getPosition(), 10, 20, 30);
	getWorld()->addLight(_light);
}

void Gunshot::removed() {
	getWorld()->removeLight(_light);
}

void Gunshot::update(float dt) {
	_elapsed += dt;
	
	float ramp = (0.1 - _elapsed) / 0.1;
	
	_light->setColor(Color(252/255.0 * ramp, 238/255.0 * ramp, 128/255.0 * ramp));
	
	if (_elapsed >= 0.1) {
		getWorld()->removeEntity(this);
	}
}