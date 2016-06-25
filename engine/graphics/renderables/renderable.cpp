#include "renderable.h"

Renderable::Renderable(Engine* engine) : _program(), _engine(engine) {
}

Renderable::~Renderable() {
}
	
Resource<Program> Renderable::getProgram() const {
	return _program;
}

void Renderable::setProgram(Resource<Program> p) {
	_program = p;
}
	