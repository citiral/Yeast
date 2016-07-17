#pragma once

#include "../primitives/program.h"
#include "../../math/Vector2.h"
#include "../../engine.h"
#include "../../resources/resource.h"
#include "../../scripting/LuaEngine.h"


class Renderable : public LuaCustomPush {
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
