#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H

#include "../../engine/Entity.h" // Base class: Entity

class PlayerEntity : public Entity
{
public:
	PlayerEntity(Engine* engine, float y);
	virtual ~PlayerEntity();

	virtual
void added();
	virtual
void removed();
	virtual
void update(float dt);


	virtual void onMoveCollideX(Entity* e, float amount);
	virtual void onMoveCollideY(Entity* e, float amount);

private:
	float _XmaxSpeed;
	float _YmaxSpeed;
	float _Xspeed;
	float _Yspeed;
	float _shootCooldown;
};

#endif // PLAYERENTITY_H
