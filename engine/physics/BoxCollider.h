#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <memory>
#include "Collider.h"
#include "../math/Vector2.h"
class BoxCollider : public Collider
{
public:
	BoxCollider(float width, float height);
	virtual ~BoxCollider();

	virtual bool collidesWith(const Collider& other) const;
	virtual void resolveCollision(const Collider& other, std::function<void(float)> xCallback, std::function<void(float)> yCallback);
	virtual float getBoundingWidth() const;
	virtual float getBoundingHeight() const;
	
	float getWidth() const;
	float getHeight() const;
	void setWidth(float width);
	void setHeight(float height);
	
	Vector2 getOrigin() const;
	void setOrigin(const Vector2& v);
	
	void centerOrigin();

	void push(lua_State* L, Collider* ptr);
	void push(lua_State* L, std::shared_ptr<Collider> ptr);
private:
	float _width;
	float _height;
	Vector2 _origin;
	
};

#endif // BOXCOLLIDER_H
