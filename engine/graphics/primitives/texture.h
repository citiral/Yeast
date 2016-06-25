#pragma once

#include <string>

class GL30Texture {
public:

	GL30Texture(int width, int height, int channels = 3);
	GL30Texture(const std::string& path);
	~GL30Texture();

	int getWidth() const;
	int getHeight() const;
	int getChannels() const;

	/**
	 * @brief Flushes the texture changes. This must be called in order to see the changes on the texture (such as pixel changes, etc)
	 */
	void flush();
	
	/**
	 * @brief Sets the wrap of the texture mode needs to be a valid opengl enum:
	 * GL_CLAMP_TO_EDGE
	 * GL_CLAMP_TO_BORDER
	 * GL_REPEAT
	 * ..
	 */
	void setRepeat(unsigned int mode);

	void enableTexture(unsigned int index);

private:
	void loadSoilTexture(const std::string& path);
	void createOpenglTexture();

	int _width;
	int _height;
	int _channels;

	bool _isSoilImage;
	unsigned char* _textureData;

	unsigned int _openglTexture;

};
