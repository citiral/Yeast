#ifndef LIGHT_H
#define LIGHT_H

#include "../primitives/program.h"
#include "../../resource.h"
#include "../../engine.h"

class Light
{
public:
    Light(Engine* engine);
    virtual ~Light();

    virtual void enableForRender() = 0;

    Resource<Program> getProgram() const;
    void setProgram(Resource<Program> p);

protected:
    Engine* _engine;

private:
    Resource<Program> _program;
};

#endif // LIGHT_H