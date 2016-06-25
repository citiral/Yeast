#pragma once

class Quad {
private:
    Quad();
    ~Quad();
    static Quad* _quad;

public:
    static Quad* getQuad();
    void use();
    void draw();

private:
    void generateVBO();

    unsigned int _vbo;
    unsigned int _vao;
};