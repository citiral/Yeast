#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class FrameBuffer
{
public:
	FrameBuffer(unsigned int textureAmount, int width, int height, int mipmaps = 0);
	virtual ~FrameBuffer();
	
	void bindRead();
	void bindDraw();
	void bindAll();
	
	void checkErrors();
	
	unsigned int getTextureAmount();
	unsigned int getTexture(int texture);
	
	static void bindDefaultFramebuffer();
	
private:
	void createFramebuffer();
	
	//size of the framebuffer
	int _width;
	int _height;
	int _mipmaps;
	//amount of textures in the fbo
	int _textureAmount;
	//array of textures of the fbo
	unsigned int* _textures;
	//the id of the fbo itself
	unsigned int _framebuffer;

};

#endif // FRAMEBUFFER_H
