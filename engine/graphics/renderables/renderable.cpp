#include "renderable.h"

Renderable::Renderable(Engine* engine) :_engine(engine), _program() {
}

Renderable::~Renderable() {
}

std::shared_ptr<Program> Renderable::getProgram() const {
	return _program;
}

void Renderable::setProgram(std::shared_ptr<Program> p) {
	_program = p;
}
	