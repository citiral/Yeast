#pragma once

#include "../primitives/program.h"
#include "../../math/Vector2.h"
#include "../../resource.h"
#include "../../engine.h"

class Renderable {
public:
    Renderable(Engine* engine);
    virtual ~Renderable();

    virtual void enableForRender() = 0;
	
	Resource<Program> getProgram() const;
	void setProgram(Resource<Program> p);

protected:
    Engine* _engine;

private:
	Resource<Program> _program;
};
