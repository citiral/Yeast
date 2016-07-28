//
// Created by Olivier on 7/22/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_CALCULATEMAXLUM_H
#define I_WANNA_KILL_THE_BOSHY_CALCULATEMAXLUM_H

#include "../primitives/color.h"
#include "../../engine.h"

/**
 * Can calculate the max luminance of a texture from the given width and height
 */
class CalculateMaxLum {
public:
    CalculateMaxLum(Engine* engine, unsigned int width, unsigned int height);
    ~CalculateMaxLum();

    void allocate();
    void deallocate();

    // returns the maximum luminance of the given opengl texture
    Color getMaxLum(unsigned int texture);

private:
    Engine* _engine;
    unsigned int _width;
    unsigned int _height;
    unsigned int _fbo1;
    //unsigned int _fbo2;
    unsigned int _texture;
};


#endif //I_WANNA_KILL_THE_BOSHY_CALCULATEMAXLUM_H
