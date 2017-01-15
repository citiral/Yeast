#include "texture.h"
#include <iostream>
#include <SOIL.h>
#include <glad/glad.h>

GL30Texture::GL30Texture(const std::string& path)
{
	_isSoilImage = true;
	_openglTexture = 0;

	loadSoilTexture(path);
	createOpenglTexture();
}

GL30Texture::GL30Texture(int width, int height, int channels)
{
	_isSoilImage = false;
	_width = width;
	_height = height;
	_channels = channels;

	_textureData = new unsigned char[_width * _height * _channels];

	createOpenglTexture();
}

GL30Texture::~GL30Texture()
{
	if (_isSoilImage)
		SOIL_free_image_data(_textureData);
	else
		delete[] _textureData;
}

bool GL30Texture::hotSwap(const std::string& path) {
    if (_isSoilImage) {
        SOIL_free_image_data(_textureData);
        loadSoilTexture(path);
        createOpenglTexture();
        return 0; // success
    }
    return 1; // failure, nothing to hotswap
}

void GL30Texture::createOpenglTexture()
{
	//create the texture
	glGenTextures(1, &_openglTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _openglTexture);

	flush();
}

void GL30Texture::flush() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _openglTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _textureData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	setRepeat(GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);
}

void GL30Texture::setRepeat(unsigned int mode) {
	enableTexture(0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void GL30Texture::enableTexture(unsigned int index) {
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, _openglTexture);
}

void GL30Texture::loadSoilTexture(const std::string& path)
{
	_textureData = SOIL_load_image(path.c_str(), &_width, &_height, &_channels, SOIL_LOAD_RGBA);
	if (_textureData == nullptr) {
		std::cout << "Failed opening file " << path << std::endl;
	}
}

int GL30Texture::getWidth() const {
	return _width;
}

int GL30Texture::getHeight() const {
	return _height;
}

int GL30Texture::getChannels() const {
	return _channels;
}
