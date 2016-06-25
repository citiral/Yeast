#ifndef SMALLLOGO_H
#define SMALLLOGO_H

#include "../../engine/Entity.h"

class SmallLogo : public Entity
{
public:
	SmallLogo(Engine* engine);
	virtual ~SmallLogo();
	
	virtual void added();
	virtual void removed();
	virtual void update(float dt);
};

#endif // SMALLLOGO_H
