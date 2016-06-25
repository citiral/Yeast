#include "program.h"
#include <glad/glad.h>

Program::Program(unsigned int vertex, unsigned int fragment) {
	_program = glCreateProgram();

    glAttachShader(_program, vertex);
    glAttachShader(_program, fragment);
	
	glLinkProgram(_program);
}

Program::~Program() {
    glDeleteProgram(_program);
}

void Program::enableProgram() {
    glUseProgram(_program);
}

unsigned int Program::getProgramID() {
    return _program;
}
