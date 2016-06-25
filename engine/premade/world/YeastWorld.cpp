#include "YeastWorld.h"
#include "../entities/biglogo.h"

YeastWorld::YeastWorld(Engine* engine, World* nextWorld):
    World(engine)
{
    _nextWorld = nextWorld;
}

YeastWorld::~YeastWorld()
{
}

void YeastWorld::added() {
	elapsed = 0;
    _light = new AmbientLight(getEngine(), Color(0, 0, 0));
    this->addLight(_light);
	this->addEntity(new Biglogo(getEngine()));
}


void YeastWorld::update(float dt) {
	World::update(dt);

	elapsed += dt;

    if (elapsed < 1.5)
        _light->setColor(Color(1, 1, 1) * (elapsed / 1.5));
    else
        _light->setColor(Color(1, 1, 1) * (1-((elapsed - 1.5) / 1.5)));
		
	if (elapsed > 3) {
		getEngine()->setWorld(_nextWorld);
	}
}

void YeastWorld::removed() {

}