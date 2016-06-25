#ifndef GENERICBACKGROUND_H
#define GENERICBACKGROUND_H

#include <string>

#include "../../engine/Entity.h" // Base class: Entity

class GenericBackground : public Entity
{
public:
	GenericBackground(Engine* engine, const std::string& backgroundname, float size);
	virtual ~GenericBackground();
	
	virtual void added();
	virtual void removed();
	virtual void update(float dt);
	
private:
	std::string _path;
	float _size;
};

#endif // GENERICBACKGROUND_H
