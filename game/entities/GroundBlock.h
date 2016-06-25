#ifndef GROUNDBLOCK_H
#define GROUNDBLOCK_H

#include "../../engine/Entity.h" // Base class: Entity

class GroundBlock : public Entity
{
public:
	GroundBlock(Engine* engine, float x, float y);
	virtual ~GroundBlock();

	virtual
void added();
	virtual
void removed();
	virtual
void update(float dt);
};

#endif // GROUNDBLOCK_H
