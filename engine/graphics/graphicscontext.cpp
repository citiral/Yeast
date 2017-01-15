#include "../engine.h"
#include "../resources/ResourceManager.h"
#include "graphicscontext.h"
#include <glad/glad.h>
#include "primitives/quad.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
//#include "renderables/color.h"
//#include "renderables/texture.h"

GraphicsContext::GraphicsContext(Engine* engine, int width, int height) {
    _width = width;
    _height = height;
	_gbuffer = nullptr;
    _post1 = nullptr;
    _post2 = nullptr;
    _curPost = 0;
    _engine = engine;
    _tonemapScale = 0.17;
    _tonemapTargetMaxLum = 1;
}

GraphicsContext::~GraphicsContext() {
    terminate();
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
	_gbuffer = new FrameBuffer(3, _width, _height);
	_gbuffer->checkErrors();

	// create the postprocessing framebuffers
	_post1 = new FrameBuffer(1, _width, _height);
	_post1->checkErrors();
	_post2 = new FrameBuffer(1, _width, _height);
	_post2->checkErrors();

    // create the tonemapping framebuffer using mipmaps to downscale
    _tonemapping_avg = new FrameBuffer(1, _width, _height, (int)std::floor(std::log2(std::max(_width, _height))));
    //_calculatemaxlum = new CalculateMaxLum(_engine, _width, _height);
    _curPost = 0;
	
	std::cout << "opengl version is: " << glGetString(GL_VERSION) << std::endl;
        
	//return the opengl load status
	return 1;
}

void GraphicsContext::terminate() {
    delete _gbuffer;
    //delete _calculatemaxlum;
    delete _post1;
    delete _post2;
    delete _tonemapping_avg;
}

void GraphicsContext::beginStep1Composition() {
    _gbuffer->bindAll();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );
}

//TODO clean up all clears, etc
void GraphicsContext::beginStep2Lighting() {
    _curPost = 0;
	_post1->bindAll();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glBlendFunc(GL_ONE, GL_ONE);
}

void GraphicsContext::beginStep3PostProcessing() {
    flipPost();
    glDisable(GL_BLEND);
}

void GraphicsContext::beginStep4Finalize() {
    FrameBuffer::bindDefaultFramebuffer();
}

void GraphicsContext::drawRenderable(Renderable& renderable, Vector2 position, float rotation, Vector2 scale) {
   //enable the renderable to get rendered
   renderable.enableForRender();
   
   //set the uniforms
   glUniform2f(renderable.getProgram()->getUniform("position"), position.getX(), position.getY());
   glUniform2f(renderable.getProgram()->getUniform("resolution"), _width, _height);
   glUniform2f(renderable.getProgram()->getUniform("scale"), scale.getX(), scale.getY());
   glUniform1f(renderable.getProgram()->getUniform("rotation"), rotation);
   
   //and draw the quad
   Quad::getQuad()->draw();
}

void GraphicsContext::drawLight(Light& light) {
	//enable the light itself for rendering
	light.enableForRender();

	//set the uniform location for the g-buffer textures
	glUniform1i(light.getProgram()->getUniform("diffuse"), 0);
	glUniform1i(light.getProgram()->getUniform("normal"), 1);
	glUniform1i(light.getProgram()->getUniform("info"), 2);
	glUniform2f(light.getProgram()->getUniform("resolution"), _width, _height);

	//bind the g-buffer textures to the light
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _gbuffer->getTexture(0));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _gbuffer->getTexture(1));
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _gbuffer->getTexture(2));

	Quad::getQuad()->draw();
}

void GraphicsContext::flipPost() {
    if (_curPost == 0) {
        _curPost = 1;
        _post2->bindAll();
    } else {
        _curPost = 0;
        _post1->bindAll();
    }
}

FrameBuffer* GraphicsContext::readPost() {
    if (_curPost == 0) {
        return _post2;
    } else {
        return _post1;
    }
}

FrameBuffer* GraphicsContext::writePost() {
    if (_curPost == 0) {
        return _post1;
    } else {
        return _post2;
    }
}

void GraphicsContext::PostTonemap() {
    // first calculate the log avg of the luminance
    _tonemapping_avg->bindAll();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, readPost()->getTexture(0));
    std::shared_ptr<Program> prog = _engine->getResourceManager()->loadProgram("res/shaders/post/post.vsh", "res/shaders/post/tonemap_logavg.fsh");
    prog->enableProgram();
    glUniform2f(glGetUniformLocation(prog->getProgramID(), "size"), _width, _height);
    Quad::getQuad()->draw();

    // generate the mipmaps so we can get the average value
    glBindTexture(GL_TEXTURE_2D, _tonemapping_avg->getTexture(0));
    glGenerateMipmap(GL_TEXTURE_2D);

    // retrieve the average color
    // float avg[4];
    // glGetTexImage(GL_TEXTURE_2D, (int)std::floor(std::log2(std::max(_width, _height))), GL_RGB, GL_FLOAT, avg);

    // now calculate the max color, for this we will manually fill the mipmaps
    // Color c = _calculatemaxlum->getMaxLum(readPost()->getTexture(0));

    // now use that to properly tonemap
    writePost()->bindAll();
    prog = _engine->getResourceManager()->loadProgram("res/shaders/post/post.vsh", "res/shaders/post/tonemap.fsh");
    prog->enableProgram();

    glUniform1f(prog->getUniform("lwhite"), _tonemapTargetMaxLum);
    glUniform1f(prog->getUniform("a"), _tonemapScale);
    glUniform2f(prog->getUniform("size"), _width, _height);

    glUniform1i(prog->getUniform("screen"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, readPost()->getTexture(0));
    glUniform1i(prog->getUniform("avg_buffer"), 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _tonemapping_avg->getTexture(0));

    Quad::getQuad()->draw();
    flipPost();
}

void GraphicsContext::PostFinalize() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, readPost()->getTexture(0));
    std::shared_ptr<Program> prog = _engine->getResourceManager()->loadProgram("res/shaders/post/post.vsh", "res/shaders/post/finalize.fsh");
    prog->enableProgram();
    glUniform2f(glGetUniformLocation(prog->getProgramID(), "size"), _width, _height);
    Quad::getQuad()->draw();
    flipPost();
}

void GraphicsContext::setTonemapTargetMaxLum(float targetMaxLum) {
    _tonemapTargetMaxLum = targetMaxLum;
}

float GraphicsContext::getTonemapTargetMaxLum() const {
    return _tonemapTargetMaxLum;
}

void GraphicsContext::setTonemapScale(float targetscale) {
    _tonemapScale = targetscale;
}

float GraphicsContext::getTonemapScale() const {
    return _tonemapScale;
}


















