
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

    void push(lua_State* L, Light* val);
    void push(lua_State* L, std::shared_ptr<Light> val);
};

#endif // FULLBRIGHTLIGHT_H