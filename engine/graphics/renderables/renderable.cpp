#include "renderable.h"

Renderable::Renderable(Engine* engine) :_engine(engine), _program() {
}

Renderable::~Renderable() {
}
	
Resource<Program> Renderable::getProgram() const {
	return _program;
}

void Renderable::setProgram(Resource<Program> p) {
	_program = p;
}
	