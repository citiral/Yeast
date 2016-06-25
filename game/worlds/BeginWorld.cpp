#include "BeginWorld.h"
#include "../entities/GenericBackground.h"
#include "../entities/GroundBlock.h"
#include "../entities/BoxTest.h"
#include "../entities/Alien.h"
#include "../entities/SmallLogo.h"
#include <cstdlib>

BeginWorld::BeginWorld(Engine* engine): World(engine)
{
}

BeginWorld::~BeginWorld()
{
}

void BeginWorld::added() {
	elapsed = 0;
	spawntimer = 0;
	this->addLight(new AmbientLight(getEngine(), Color(64/255.0 *0.5, 156/255.0 * 0.5, 255/255.0 * 0.5)));
	
	_lights[0] = new PointLight(getEngine(), Color(1, 1, 0), Vector2(683,393), 100, 0, 200.0);
	_lights[1] = new PointLight(getEngine(), Color(1, 1, 0), Vector2(683,393), 100, 50, 200.0);
	_lights[2] = new PointLight(getEngine(), Color(1, 1, 0), Vector2(683,393), 100, 100, 200.0);
	_lights[3] = new PointLight(getEngine(), Color(1, 1, 0), Vector2(683,393), 100, 150, 200.0);
	_lights[4] = new PointLight(getEngine(), Color(1, 1, 0), Vector2(683,393), 100, 180, 200.0);
	_lights[5] = new PointLight(getEngine(), Color(1, 1, 0), Vector2(683,393), 100, 200, 200.0);
	
	for (int i = 0 ; i < 6 ; i++)
		this->addLight(_lights[i]);
	
	addEntity(new GenericBackground(getEngine(), "res/assets/masonry-wall.jpg", 0.2));
	_player = new PlayerEntity(getEngine(), 250);
	addEntity(_player);
	
	addEntity(new SmallLogo(getEngine()));
}

void BeginWorld::spawnAlien() {

}

void BeginWorld::update(float dt) {
	World::update(dt);
	
	elapsed += dt;
	
	spawntimer += dt;
	if (spawntimer > 1) {
		spawntimer -= 1;
		spawnAlien();
	}
	
	for (int i = 0 ; i < 6 ; i++) {
		_lights[i]->setPosition(Vector2(683,393) + Vector2(0,250).rotate(elapsed + (3.1415 / 3) * i));
		//getEntity(1)->setRotation(elapsed);
	}
}

void BeginWorld::removed() {

}