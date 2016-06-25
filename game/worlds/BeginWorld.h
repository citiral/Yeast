#ifndef BEGINWORLD_H
#define BEGINWORLD_H

#include "../../engine/World.h"
#include "../../engine/graphics/lighting/AmbientLight.h"
#include "../../engine/graphics/lighting/PointLight.h"
#include "../entities/PlayerEntity.h"

class BeginWorld : public World
{
public:
	BeginWorld(Engine* engine);
	virtual ~BeginWorld();
	
	virtual void added();
	virtual void update(float dt);
	virtual void removed();
	
private:
	PlayerEntity* _player;
	void spawnAlien();
	PointLight* _lights[6];
	float elapsed;
	float spawntimer;
};

#endif // BEGINWORLD_H
