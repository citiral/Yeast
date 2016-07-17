#pragma once

#include "../primitives/program.h"
#include "../../math/Vector2.h"
#include "../../engine.h"
#include "../../resources/resource.h"
#include "../../scripting/LuaEngine.h"
#include <memory>

class Renderable : public LuaCustomPush<Renderable> {
public:
    Renderable(Engine* engine);
    virtual ~Renderable();

    virtual void enableForRender() = 0;

    std::shared_ptr<Program> getProgram() const;
	void setProgram(std::shared_ptr<Program> p);

protected:
    Engine* _engine;

private:
    std::shared_ptr<Program> _program;
};
