#ifndef COLORFIELD_H
#define COLORFIELD_H

#include "renderable.h"
#include "../primitives/color.h"
#include "../../math/Vector2.h"

class ColorField : public Renderable
{
public:
	ColorField(Engine* engine, const Color& color, Vector2 size);
	virtual ~ColorField();

    virtual void enableForRender();
	
	Color& getColor();
	Vector2& getSize();

    void push(lua_State* L, Renderable* ptr);
    void push(lua_State* L, std::shared_ptr<Renderable> ptr);
private:
	Color _color;
	Vector2 _size;
};

#endif // COLORFIELD_H
