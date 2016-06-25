#pragma once

class Program {
public:
    Program(unsigned int vertex, unsigned int fragment);
    ~Program();

    void enableProgram();
    unsigned int getProgramID();

private:
    unsigned int _program;
};
