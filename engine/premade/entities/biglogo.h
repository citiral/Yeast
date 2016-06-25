#ifndef BIGLOGO_H
#define BIGLOGO_H

#include "../../../engine/graphics/renderables/sprite.h"
#include "../../Entity.h"

class Biglogo : public Entity
{
public:
	Biglogo(Engine* engine);
	virtual ~Biglogo();
	
	void added();
	void removed();
    void update(float dt);

};

#endif // BIGLOGO_H
