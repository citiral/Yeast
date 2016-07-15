#ifndef VECTOR2_H
#define VECTOR2_H

#include <lua.hpp>

class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& v);
	~Vector2();
	
	void setX(float x);
	void setY(float y);
	float getX() const;
	float getY() const;
	
	float length() const;
	
	float dot(const Vector2& v) const;
	Vector2 cross() const;
	Vector2 normalize() const;
	Vector2 rotate(float angle) const;

    Vector2 clone() const;
	
	Vector2 operator*(float s) const;
	Vector2 operator/(float s) const;
	
	Vector2 operator+(const Vector2& v) const;
	Vector2 operator-(const Vector2& v) const;
	Vector2 operator-() const;
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator=(const Vector2& v);
	
private:
	float _x;
	float _y;
};

#endif // VECTOR2_H
