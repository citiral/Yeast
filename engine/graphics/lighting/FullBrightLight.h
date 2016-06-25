
#ifndef FULLBRIGHTLIGHT_H
#define FULLBRIGHTLIGHT_H

#include "light.h"
#include "../../engine.h"

class FullBrightLight : public Light
{
public:
    FullBrightLight(Engine* engine);
    virtual ~FullBrightLight();

    virtual void enableForRender();
};

#endif // FULLBRIGHTLIGHT_H