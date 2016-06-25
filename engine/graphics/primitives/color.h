#pragma once

class Color {
public:
    Color(float r = 0, float g = 0, float b = 0);
	Color(const Color& c);
    ~Color();

    void setRGB(float r, float g, float b);
    void setR(float r);
    void setG(float g);
    void setB(float b);

    float getR() const;
    float getG() const;
    float getB() const;

    Color operator/(float v) const;
    Color operator*(float v) const;

private:
    float _r;
    float _g;
    float _b;

};
