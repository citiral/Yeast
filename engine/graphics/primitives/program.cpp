#include "program.h"
#include "../../resources/resource.h"
#include <glad/glad.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <utility>

Program::Program(unsigned int vertex, unsigned int fragment) {
	_program = glCreateProgram();

    glAttachShader(_program, vertex);
    glAttachShader(_program, fragment);
	
	glLinkProgram(_program);
}

Program::Program(std::pair<std::string, std::string> shaders) {
    unsigned int vertexShader = loadShader(std::get<0>(shaders), GL_VERTEX_SHADER);
    unsigned int fragmentShader = loadShader(std::get<1>(shaders), GL_FRAGMENT_SHADER);

    _program = glCreateProgram();

    glAttachShader(_program, vertexShader);
    glAttachShader(_program, fragmentShader);

    glLinkProgram(_program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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

unsigned int Program::loadShader(std::string& path, unsigned int type) {
    std::fstream file;
    file.open(path, std::fstream::in);

    if (file.is_open()) {
        std::vector<const char *> code;
        //load the file in
        while (!file.eof()) {
            char *temp = new char[512];
            file.getline(temp, 510);
            int readcount = file.gcount();
            //we don't need to replace on the last line
            if (temp[readcount - 1] == '\0') {
                temp[readcount - 1] = '\n';
                temp[readcount] = '\0';
            }
            code.push_back(temp);
        }

        //compile the shader
        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, code.size(), code.data(), nullptr);
        glCompileShader(shader);

        //BEGIN error checking
        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, 0, &errorLog[0]);

            // Provide the infolog in whatever manor you deem best.
            std::cout << "error compiling shader [" << path << "]: " << errorLog.data() << std::endl;
            // Exit with failure.
            glDeleteShader(shader); // Don't leak the shader.
        }
        //END error checking

        //delete the code
        for (auto it = code.begin(); it != code.end(); it++) {
            delete *it;
        }

        return shader;
    } else {
        std::cout << "file not found: " << path << "\n";
    }
    return 0;
}

int Program::getUniform(const char* uniform) {
    auto uni = _uniforms.find(uniform);

    if (uni != _uniforms.end()) {
        return (*uni).second;
    } else {
        int location = glGetUniformLocation(_program, uniform);
        _uniforms[uniform] = location;
        return location;
    }
}


