#pragma once

#include "primitives/FrameBuffer.h"
#include "renderables/renderable.h"
#include "lighting/light.h"
#include "algorithms/CalculateMaxLum.h"

class GL30Texture;
class Color;
class Engine;

class GraphicsContext {
public:
    GraphicsContext(Engine* engine, int width = 800, int height = 600);
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

	void setTonemapTargetMaxLum(float targetMaxLum);
	float getTonemapTargetMaxLum() const;
	void setTonemapScale(float targetscale);
	float getTonemapScale() const;

	void PostTonemap();

	void PostFinalize();

    int getWidth();
    int getHeight();

private:
	void flipPost();
	FrameBuffer* readPost();
	FrameBuffer* writePost();

	Engine* _engine;
	int _width;
    int _height;
    float _backR;
    float _backG;
    float _backB;
	int _curPost;
	FrameBuffer* _gbuffer;
	FrameBuffer* _post1;
	FrameBuffer* _post2;
	FrameBuffer* _tonemapping_avg;
	//CalculateMaxLum* _calculatemaxlum;

	// tonemapping
	float _tonemapTargetMaxLum;
	float _tonemapScale;

};