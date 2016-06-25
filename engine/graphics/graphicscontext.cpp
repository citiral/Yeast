#include "graphicscontext.h"
#include <glad/glad.h>
#include "primitives/quad.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
//#include "renderables/color.h"
//#include "renderables/texture.h"

GraphicsContext::GraphicsContext(int width, int height) {
    _width = width;
    _height = height;
	_fbo = nullptr;
}

GraphicsContext::~GraphicsContext() {
	if (_fbo != nullptr)
		delete _fbo;
}

void GraphicsContext::setBackground(float r, float g, float b) {
    _backR = r;
    _backG = g;
    _backB = b;
    glClearColor(r, g, b, 1);
}

void GraphicsContext::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );
	glDisable(GL_DEPTH_TEST);
	glDepthMask(false);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

int GraphicsContext::getWidth() {
	return _width;
}

int GraphicsContext::getHeight() {
	return _height;
}

bool GraphicsContext::initialize() {
    //load opengl using GLAD
    if(!gladLoadGL()) { exit(-1); };
    printf("OpenGL Version %d.%d loaded", GLVersion.major, GLVersion.minor);


    //set the viewport of the default framebuffer
	glViewport(0, 0, _width, _height);
	
	//create the gbuffer
	//GBUFFER LAYOUT:
	//COLOR0: (COLOR)
	//COLOR1: (NORMAL)
	//COLOR2: LIT, UNUSED, UNUSED
	_fbo = new FrameBuffer(3, _width, _height);
	_fbo->checkErrors();
	
	std::cout << "opengl version is: " << glGetString(GL_VERSION) << std::endl;
	
	/*if (!GLAD_GL_VERSION_3_0) {
		std::cout << "glad does not support this version of opengl" << std::endl;
	}
	*/
        
	//return the opengl load status
	return 1;
}

void GraphicsContext::terminate() {

}

void GraphicsContext::beginStep1Composition() {
	_fbo->bindAll();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );
}

//TODO clean up all clears, etc
void GraphicsContext::beginStep2Lighting() {
	_fbo->bindDefaultFramebuffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glBlendFunc(GL_ONE, GL_ONE);
	glEnable( GL_BLEND );
}

void GraphicsContext::beginStep3PostProcessing() {

}

void GraphicsContext::beginStep4Finalize() {

}

void GraphicsContext::drawRenderable(Renderable& renderable, Vector2 position, float rotation, Vector2 scale) {
   //enable the renderable to get rendered
   renderable.enableForRender();
   
   //set the uniforms
   glUniform2f(glGetUniformLocation(renderable.getProgram()->getProgramID(), "position"), position.getX(), position.getY());
   glUniform2f(glGetUniformLocation(renderable.getProgram()->getProgramID(), "resolution"), _width, _height);
   glUniform2f(glGetUniformLocation(renderable.getProgram()->getProgramID(), "scale"), scale.getX(), scale.getY());
   glUniform1f(glGetUniformLocation(renderable.getProgram()->getProgramID(), "rotation"), rotation);
   
   //and draw the quad
   Quad::getQuad()->draw();
}

void GraphicsContext::drawLight(Light& light) {
	//enable the light itself for rendering
	light.enableForRender();

	//set the uniform location for the g-buffer textures
	glUniform1i(glGetUniformLocation(light.getProgram()->getProgramID(), "diffuse"), 0);
	glUniform1i(glGetUniformLocation(light.getProgram()->getProgramID(), "normal"), 1);
	glUniform1i(glGetUniformLocation(light.getProgram()->getProgramID(), "info"), 2);
	glUniform2f(glGetUniformLocation(light.getProgram()->getProgramID(), "resolution"), _width, _height);

	//bind the g-buffer textures to the light
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _fbo->getTexture(0));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _fbo->getTexture(1));
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _fbo->getTexture(2));

	Quad::getQuad()->draw();
}
