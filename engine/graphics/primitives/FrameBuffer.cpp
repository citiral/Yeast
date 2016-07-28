#include "FrameBuffer.h"
#include <glad/glad.h>
#include <iostream>

FrameBuffer::FrameBuffer(unsigned int textureAmount, int width, int height, int mipmaps)
{
	_width = width;
	_height = height;
	_mipmaps = mipmaps;
	_textureAmount = textureAmount;
	// we allocate one more for the depth buffer
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
	// first, let us generate the textures
	glGenTextures(_textureAmount+1, _textures);
	
	// now we set up all textures, except the depth buffer
	for (int i = 0 ; i < _textureAmount ; i++) {
		// first bind the texture
		glBindTexture(GL_TEXTURE_2D, _textures[i]);

        // now allocate the space of the textures
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, _width, _height, 0, GL_RGBA, GL_FLOAT, NULL);

		// then set the proper parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL , _mipmaps);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD , _mipmaps);


        // and generate the mipmaps
        glGenerateMipmap(GL_TEXTURE_2D);

	}
	
	// now we create the framebuffer itself
	glGenFramebuffers(1, &_framebuffer);
	
	// we bind the framebuffer, so we are working with it
	bindAll();
	
	// now we link all the textures to the framebuffer
	for (size_t i = 0 ; i < _textureAmount ; i++) {
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+i, GL_TEXTURE_2D, _textures[i], 0);
	}
	
	// and we set up the amount of color buffers
	
	GLenum* DrawBuffers = new GLenum[_textureAmount];

	for (size_t i = 0 ; i < _textureAmount ; i++)
		DrawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
	glDrawBuffers(_textureAmount, DrawBuffers);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	delete DrawBuffers;
}

void FrameBuffer::bindDefaultFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}