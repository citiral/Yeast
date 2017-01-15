#pragma once

#include <string>
#include <map>

class Program {
public:
    Program(unsigned int vertex, unsigned int fragment);
    Program(std::pair<std::string, std::string> shaders);
    ~Program();

    int getUniform(const char* uniform);

    void enableProgram();
    unsigned int getProgramID();

private:
    unsigned int loadShader(std::string& path, unsigned int type);
    unsigned int _program;
    std::map<const char*, int> _uniforms;
};
