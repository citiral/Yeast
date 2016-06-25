#ifndef ALIEN_H
#define ALIEN_H

#include "Entity.h"
#include "PlayerEntity.h"

class Alien : public Entity
{
public:
	Alien(Engine* engine,Entity* target, const Vector2& pos);
	virtual ~Alien();
	
	void added();
	void removed();
	void update(float dt);

private:
	Entity* _target;

};

#endif // ALIEN_H
