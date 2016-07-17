#ifndef SPRITE_H
#define SPRITE_H

#include "renderable.h"
#include "../primitives/texture.h"
#include "../../resources/resource.h"
#include "../../math/Vector2.h"

class Sprite : public Renderable
{
public:
	Sprite(Engine* engine, const std::shared_ptr<GL30Texture>& diffuse);
	virtual ~Sprite();
	
	void setDiffuse(std::shared_ptr<GL30Texture> texture);
    std::shared_ptr<GL30Texture> getDiffuse() const;
	
	void setNormal(std::shared_ptr<GL30Texture> texture);
    std::shared_ptr<GL30Texture> getNormal() const;
	
	bool getLit() const;
	void setLit(bool isLit);
	
    virtual void enableForRender();
	
	//sets the origin of the sprite on the center of the diffuse texture.
	void centerOrigin();
	Vector2 getOrigin() const;
	void setOrigin(const Vector2& v);

    void push(lua_State* L, Renderable* ptr);
    void push(lua_State* L, std::shared_ptr<Renderable> ptr);
private:
    std::shared_ptr<GL30Texture> _diffuse;
    std::shared_ptr<GL30Texture> _normal;
	Vector2 _origin;
	bool _isLit;
};

#endif // SPRITE_H
