#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"
#include "../primitives/color.h"
#include "../../math/Vector2.h"

class PointLight : public Light
{
public:
    PointLight(Engine* engine, const Color& color, const Vector2& position, float depth, float drop, float end);
    virtual ~PointLight();

    Color& getColor();
    void setColor(Color c);

    Vector2& getPosition();
    void setPosition(Vector2 p);

    float getDrop() const;
    void setDrop(float drop);

    float getEnd() const;
    void setEnd(float end);

    virtual void enableForRender();

private:
    Color _lightColor;
    Vector2 _position;
    float _drop;
    float _end;
    float _depth;
};

#endif // POINTLIGHT_H