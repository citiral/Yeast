#include "GroundBlock.h"

#include "../../engine/graphics/renderables/sprite.h"
#include "../../engine/physics/BoxCollider.h"
#include "../../engine/resourceloader.h"

GroundBlock::GroundBlock(Engine* engine, float x, float y): Entity(engine)
{
	setPosition(x, y);
	Sprite* sprite = new Sprite(getEngine(), getEngine()->getResourceLoader()->loadTexture("res/assets/grassMid_diffuse.png"));
	setRenderable(sprite);
	setCollider(new BoxCollider(sprite->getDiffuse()->getWidth(), sprite->getDiffuse()->getHeight()));
}

GroundBlock::~GroundBlock()
{
}

void GroundBlock::added()
{
}

void GroundBlock::removed()
{
}

void GroundBlock::update(float dt)
{
}
