#include "SmallLogo.h"

#include "../../engine/graphics/renderables/sprite.h"
#include "../../engine/resourceloader.h"

SmallLogo::SmallLogo(Engine* engine): Entity(engine)
{
}

SmallLogo::~SmallLogo()
{
}

void SmallLogo::added() {
	setRenderable(new Sprite(getEngine(), getEngine()->getResourceLoader()->loadTexture("res/assets/small logo.png")));
	((Sprite*) getRenderable())->setLit(false);
	
	setX(20);
	setY(WINDOW->getHeight() - ((Sprite*) getRenderable())->getDiffuse()->getHeight() - 20);
}

void SmallLogo::removed() {
	
}

void SmallLogo::update(float dt) {
	
}

