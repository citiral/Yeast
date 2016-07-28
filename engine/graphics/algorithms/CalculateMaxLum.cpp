//
// Created by Olivier on 7/22/2016.
//

#include <glad/glad.h>
#include <cmath>
#include <algorithm>
#include "CalculateMaxLum.h"
#include "../../resources/ResourceManager.h"
#include "../primitives/quad.h"

CalculateMaxLum::CalculateMaxLum(Engine* engine, unsigned int width, unsigned int height): _engine(engine), _width(width), _height(height) {
    allocate();
}

CalculateMaxLum::~CalculateMaxLum() {
    deallocate();
}

void CalculateMaxLum::allocate() {
    // create a texture with mipmaps to 1x1
    glGenTextures(1, &_texture);

    // first bind the texture
    glBindTexture(GL_TEXTURE_2D, _texture);

    // now allocate the space of the textures
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, _width/2, _height/2, 0, GL_RGBA, GL_FLOAT, NULL);

    // then set the proper parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL , (int)std::floor(std::log2(std::max(_width, _height))) - 1);

    // and generate the mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // then generate the fbo
    glGenFramebuffers(1, &_fbo1);
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo1);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);
    glDrawBuffers(1, DrawBuffers);
}

void CalculateMaxLum::deallocate() {
    glDeleteTextures(1, &_texture);
    glDeleteFramebuffers(1, &_fbo1);
}

Color CalculateMaxLum::getMaxLum(unsigned int texture) {
    glActiveTexture(GL_TEXTURE0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo1);

    // do the first pass
    std::shared_ptr<Program> prog = _engine->getResourceManager()->loadProgram("res/shaders/post/tonemap_max.vsh", "res/shaders/post/tonemap_max.fsh");
    prog->enableProgram();
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);
    glUniform2f(glGetUniformLocation(prog->getProgramID(), "size"), _width, _height);
    glUniform1i(glGetUniformLocation(prog->getProgramID(), "mipmap"), 0);
    glUniform1i(glGetUniformLocation(prog->getProgramID(), "screen"), 0);
    glBindTexture(GL_TEXTURE_2D, texture);
    Quad::getQuad()->draw();
    glBindTexture(GL_TEXTURE_2D, _texture);

    // keep doing passes for each mipmap levle
    for (int i = 1 ; i <= (int)std::floor(std::log2(std::max(_width, _height))) - 1 ; i++) {
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, i);
        glUniform2f(glGetUniformLocation(prog->getProgramID(), "size"), _width / (i+1), _height / (i+1));
        glUniform1i(glGetUniformLocation(prog->getProgramID(), "mipmap"), i-1);
        Quad::getQuad()->draw();
    }

    // TODO figure a way to retrieve directly from the shader, so no halting occurs
    float maxc[4];
    glGetTexImage(GL_TEXTURE_2D, (int)std::floor(std::log2(std::max(_width, _height))) - 1, GL_RGB, GL_FLOAT, maxc);

    std::cout << "max color is " << maxc[0] << ", " << maxc[1] << ", " << maxc[2] << std::endl;

    return Color();
}









