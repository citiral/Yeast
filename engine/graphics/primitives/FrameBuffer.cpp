#include "FrameBuffer.h"
#include <glad/glad.h>
#include <iostream>

FrameBuffer::FrameBuffer(unsigned int textureAmount, int width, int height)
{
	_width = width;
	_height = height;
	_textureAmount = textureAmount;
	//we allocate one more for the depth buffer
	_textures = new unsigned int[textureAmount+1];
	
	createFramebuffer();
}

FrameBuffer::~FrameBuffer()
{
	//delete the textures in opengl
	glDeleteTextures(_textureAmount+1, _textures);
	//delete the array of textures
	delete _textures;
	//and delete the framebuffer in opengl
	glDeleteFramebuffers(1, &_framebuffer);
}

void FrameBuffer::bindRead() {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _framebuffer);
}

void FrameBuffer::bindDraw() {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _framebuffer);
}

void FrameBuffer::bindAll() {
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
	glViewport(0, 0, _width, _height);
}

unsigned int FrameBuffer::getTextureAmount() {
	return _textureAmount;
}

unsigned int FrameBuffer::getTexture(int texture) {
	return _textures[texture];
}

void FrameBuffer::checkErrors() {
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "error in framebuffer" << std::endl;
}

void FrameBuffer::createFramebuffer() {
	//first, let us generate the textures
	glGenTextures(_textureAmount+1, _textures);
	
	//now we set up all textures, except the depth buffer
	for (int i = 0 ; i < _textureAmount ; i++) {
		//first bind the texture
		glBindTexture(GL_TEXTURE_2D, _textures[i]);
		
		//then set the proper parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		//now allocate the space of the textures
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	} 
	//now we create the depth buffer
	/*glBindTexture(GL_TEXTURE_2D, _textures[_textureAmount]);
	
	//set up the texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	
	//and allocate the space for the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, _width, _height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);*/
	
	//now we create the framebuffer itself
	glGenFramebuffers(1, &_framebuffer);
	
	//we bind the framebuffer, so we are working with it
	bindAll();
	
	//now we link all the textures to the framebuffer
	for (int i = 0 ; i < _textureAmount ; i++) {
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+i, GL_TEXTURE_2D, _textures[i], 0);
	}
	//glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _textures[_textureAmount], 0);*/
	
	//and we set up the amount of color buffers
	
	GLenum* DrawBuffers = new GLenum[_textureAmount];

	for (int i = 0 ; i < _textureAmount ; i++)
		DrawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
	glDrawBuffers(_textureAmount, DrawBuffers);
	glColorMask(true, true, true, true);
	delete DrawBuffers;
}

void FrameBuffer::bindDefaultFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}