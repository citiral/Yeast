#include "color.h"

#include <iostream>

Color::Color(float r, float g, float b) {
    _r = r;
    _g = g;
    _b = b;
}

Color::Color(const Color& c) {
	_r = c.getR();
	_g = c.getG();
	_b = c.getB();
}

Color::~Color() {
	
}

void Color::setRGB(float r, float g, float b) {
    _r = r;
    _g = g;
    _b = b;
}

void Color::setR(float r) {
    _r = r;
}

void Color::setG(float g) {
    _g = g;
}

void Color::setB(float b) {
    _b = b;
}

float Color::getR() const {
    return _r;
}

float Color::getG() const {
    return _g;
}

float Color::getB() const {
    return _b;
}

Color Color::operator/(float v) const {
    return Color(_r / v, _g / v, _b / v);
}

Color Color::operator*(float v) const {
    return Color(_r * v, _g * v, _b * v);
}