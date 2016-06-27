#ifndef SPRITE_H
#define SPRITE_H

#include "renderable.h"
#include "../primitives/texture.h"
#include "../../resources/resource.h"
#include "../../math/Vector2.h"

class Sprite : public Renderable
{
public:
	Sprite(Engine* engine, const Resource<GL30Texture>& diffuse);
	virtual ~Sprite();
	
	void setDiffuse(Resource<GL30Texture> texture);
	Resource<GL30Texture> getDiffuse() const;
	
	void setNormal(Resource<GL30Texture> texture);
	Resource<GL30Texture> getNormal() const;
	
	bool getLit() const;
	void setLit(bool isLit);
	
    virtual void enableForRender();
	
	//sets the origin of the sprite on the center of the diffuse texture.
	void centerOrigin();
	Vector2 getOrigin() const;
	void setOrigin(const Vector2& v);
	
private:
	Resource<GL30Texture> _diffuse;
	Resource<GL30Texture> _normal;
	Vector2 _origin;
	bool _isLit;
};

#endif // SPRITE_H
