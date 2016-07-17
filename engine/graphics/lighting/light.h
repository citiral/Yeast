#ifndef LIGHT_H
#define LIGHT_H

#include "../primitives/program.h"
#include "../../resources/resource.h"
#include "../../engine.h"
#include <memory>

class Light
{
public:
    Light(Engine* engine);
    virtual ~Light();

    virtual void enableForRender() = 0;

    std::shared_ptr<Program> getProgram() const;
    void setProgram(std::shared_ptr<Program> p);

protected:
    Engine* _engine;

private:
    std::shared_ptr<Program> _program;
};

#endif // LIGHT_H