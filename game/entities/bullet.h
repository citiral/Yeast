#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(Engine* engine, const Vector2& pos, float angle);
	virtual ~Bullet();
	
	void added();
	void removed();
	void update(float dt);
	void onCollide(Entity* e);
};

#endif // BULLET_H
