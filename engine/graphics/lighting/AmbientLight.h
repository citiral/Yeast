#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "light.h"
#include "../primitives/color.h"

class AmbientLight : public Light
{
public:
    AmbientLight(Engine* engine, const Color& color);
    virtual ~AmbientLight();

    virtual void enableForRender();

    Color getColor() const;
    void setColor(const Color& c);

private:
    Color _lightColor;
};

#endif // AMBIENTLIGHT_H