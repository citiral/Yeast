#include "Vector2.h"
#include <cmath>
#include <ostream>
#include <iostream>

Vector2::Vector2() : _x(0), _y(0)
{
}

Vector2::Vector2(float x, float y) : _x(x), _y(y)
{
}

Vector2::~Vector2()
{
}

Vector2::Vector2(const Vector2& v)
{
	_x = v.getX();
	_y = v.getY();
}

Vector2 Vector2::cross() const
{
	return Vector2(_y, -_x);
}

float Vector2::dot(const Vector2& v) const
{
	return _x * v.getX() + _y * v.getY();
}

float Vector2::length() const
{
	return std::sqrt((_x*_x) + (_y * _y));
}

float Vector2::getX() const
{
	return _x;
}

float Vector2::getY() const
{
	return _y;
}

void Vector2::setX(float x)
{
	_x = x;
}

void Vector2::setY(float y)
{
	_y = y;
}

Vector2 Vector2::normalize() const
{
	return Vector2(*this / length());
}

Vector2 Vector2::rotate(float angle) const
{
	float cos = std::cos(angle);
	float sin = std::sin(angle);
	
	return Vector2(_x * cos - _y * sin, _x * sin + _y * cos);
}

Vector2 Vector2::operator +(const Vector2& v) const
{
	return Vector2(_x + v.getX(), _y + v.getY());
}

Vector2 Vector2::operator -(const Vector2& v) const
{
	return Vector2(_x - v.getX(), _y - v.getY());
}

Vector2 Vector2::operator -() const
{
	return Vector2(-_x, -_y);
}

Vector2 Vector2::operator *(float s) const
{
	return Vector2(_x * s, _y * s);
}

Vector2 Vector2::operator /(float s) const
{
	return Vector2(_x / s, _y / s);
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	_x += v.getX();
	_y += v.getY();
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
	_x -= v.getX();
	_y -= v.getY();
	return *this;	
}

Vector2& Vector2::operator=(const Vector2& v)
{
	_x = v.getX();
	_y = v.getY();
	return *this;
}

Vector2 Vector2::clone() const {
    return *this;
}
