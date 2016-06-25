#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "renderable.h"
#include "../primitives/texture.h"
#include "../../resource.h"

class Background : public Renderable
{
public:
	Background(Engine* engine, const Resource<GL30Texture>& diffuse, float scale = 1);
	virtual ~Background();
	
	void setDiffuse(Resource<GL30Texture> texture);
	Resource<GL30Texture> getDiffuse() const;
	
	void setNormal(Resource<GL30Texture> texture);
	Resource<GL30Texture> getNormal() const;

    virtual void enableForRender();
	
private:
	Resource<GL30Texture> _diffuse;
	Resource<GL30Texture> _normal;
	float _scale;

};

#endif // BACKGROUND_H
