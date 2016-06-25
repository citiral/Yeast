#ifndef BOXTEST_H
#define BOXTEST_H

#include "../../engine/Entity.h" // Base class: Entity

class BoxTest : public Entity
{
public:
	BoxTest(Engine* engine, bool moveable);
	virtual ~BoxTest();

	virtual
void added();
	virtual
void removed();
	virtual
void update(float dt);

	
	virtual void onMoveCollideX(Entity* e, float amount);
	virtual void onMoveCollideY(Entity* e, float amount);

private:
	BoxTest* other;
	bool _moveable;
};

#endif // BOXTEST_H
