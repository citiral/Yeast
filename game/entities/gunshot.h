#ifndef GUNSHOT_H
#define GUNSHOT_H

#include "../../engine/Entity.h" // Base class: Entity
#include "../../engine/graphics/lighting/PointLight.h" // Base class: Entity

class Gunshot : public Entity
{
public:
	Gunshot(Engine* engine, const Vector2& pos);
	virtual ~Gunshot();
	
	virtual void added();
	virtual void removed();
	virtual void update(float dt);
	
private:
	PointLight* _light;
	float _elapsed;
};

#endif // GUNSHOT_H
