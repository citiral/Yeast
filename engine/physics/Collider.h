#ifndef COLLIDER_H
#define COLLIDER_H

#include "../math/Vector2.h"
#include <functional>

/**
 * @class Collider
 * @author Olivier
 * @date 02/24/15
 * @file Collider.h
 * @brief all colliders are considered to have their root in the bottom-left corner. so the width and height work upwards and to the right
 */
 
 enum class ColliderType {
	 BOX,
	 NONE
 };
 
class Collider
{
public:
	Collider();
	virtual ~Collider();
	
	/**
	 * @brief This does a simple AABB check with both colliders to see if they *could be colliding. If it returns false they definately do not collide,
	 * if it returns true they might be colliding.
	 * @param other
	 * @return 
	 */
	bool couldCollideWith(const Collider& other) const;
	virtual bool collidesWith(const Collider& other) const = 0;
	virtual void resolveCollision(const Collider& other, std::function<void(float)> xCallback, std::function<void(float)> yCallback) = 0;

	const Vector2& getPos() const;
	float getX() const;
	float getY() const;
	
	void setPos(const Vector2& pos);
	void setX(float x);
	void setY(float y);
	
	bool isStatic() const;
	void setStatic(bool s);
	
	virtual float getBoundingWidth() const = 0;
	virtual float getBoundingHeight() const = 0;

	ColliderType getColliderType() const;
protected:
	ColliderType _colliderType;
	
private:
	Vector2 _pos;
	bool _static;
};

#endif // COLLIDER_H
