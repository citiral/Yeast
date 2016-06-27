#pragma once

#include <string>

class Program {
public:
    Program(unsigned int vertex, unsigned int fragment);
    Program(std::pair<std::string, std::string> shaders);
    ~Program();

    void enableProgram();
    unsigned int getProgramID();

private:
    unsigned int loadShader(std::string& path, unsigned int type);
    unsigned int _program;
};
