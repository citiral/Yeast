#pragma once

#include "primitives/FrameBuffer.h"
#include "renderables/renderable.h"
#include "lighting/light.h"

class GL30Texture;
class Color;

class GraphicsContext {
public:
    GraphicsContext(int width = 800, int height = 600);
    ~GraphicsContext();

    bool initialize();
    void terminate();

    void setBackground(float r, float g, float b);
    void clear();
	
	void beginStep1Composition();
	void beginStep2Lighting();
	void beginStep3PostProcessing();
	void beginStep4Finalize();

    void drawRenderable(Renderable& renderable, Vector2 position, float rotation, Vector2 scale);
	void drawLight(Light& light);

    int getWidth();
    int getHeight();

private:
    int _width;
    int _height;
    float _backR;
    float _backG;
    float _backB;
	FrameBuffer* _fbo;
};