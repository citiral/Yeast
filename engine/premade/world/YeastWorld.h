#ifndef YEASTWORLD_H
#define YEASTWORLD_H

#include "../../World.h"
#include "../../graphics/lighting/AmbientLight.h"

class YeastWorld : public World
{
public:
	YeastWorld(Engine* engine, World* nextWorld);
	virtual ~YeastWorld();

	virtual void added();
	virtual void update(float dt);
	virtual void removed();

private:
    World* _nextWorld;
    AmbientLight* _light;
	float elapsed;
};

#endif // YEASTWORLD_H
