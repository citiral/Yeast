#include "biglogo.h"
#include "../../../engine/resourceloader.h"

Biglogo::Biglogo(Engine* engine): Entity(engine)
{
}

Biglogo::~Biglogo()
{
}

void Biglogo::added() {
	Sprite* sprite = new Sprite(getEngine(), getEngine()->getResourceLoader()->loadTexture("res/assets/logo.png"));
	sprite->setNormal(getEngine()->getResourceLoader()->loadTexture("res/assets/logo_normal.png"));
	setRenderable(sprite);

    setX(getEngine()->getWindow()->getWidth() / 2 - sprite->getDiffuse()->getWidth() / 2);
    setY(getEngine()->getWindow()->getHeight() / 2 - sprite->getDiffuse()->getHeight() / 2);
}

void Biglogo::removed() {
	
}

void Biglogo::update(float dt) {
	

}