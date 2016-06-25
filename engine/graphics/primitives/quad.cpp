#include "quad.h"
#include <glad/glad.h>

Quad* Quad::_quad = nullptr;

Quad::Quad() {
    generateVBO();
}

Quad::~Quad() {
    glDeleteBuffers(1, &_vbo);
}

Quad* Quad::getQuad() {
    if (_quad == nullptr) {
        _quad = new Quad();
    }
    return _quad;
}

void Quad::use() {
    glBindVertexArray(_vao);
}

void Quad::draw() {
    use();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Quad::generateVBO() {
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,_vbo);

    float data[] = {
          //vertex  tex
            0, 0,
            0, 1,
            1, 1,
            1, 0
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 4, data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
}