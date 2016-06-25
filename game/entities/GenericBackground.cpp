#include "GenericBackground.h"
#include "../../engine/graphics/renderables/Background.h"
#include "../../engine/resourceloader.h"
#include <iostream>

GenericBackground::GenericBackground(Engine* engine, const std::string& backgroundname, float size): Entity(engine)
{
	_size = size;
	_path = backgroundname;
}

GenericBackground::~GenericBackground()
{
}

void GenericBackground::added() {
	std::string diffusepath = _path;
	std::string normalpath = _path;
	diffusepath.insert(diffusepath.rfind('.'), "_diffuse");
	normalpath.insert(normalpath.rfind('.'), "_normal");
	std::cout << "background path is " << diffusepath << std::endl;
	
	setRenderable(new Background(getEngine(), getEngine()->getResourceLoader()->loadTexture(diffusepath), _size));
	((Background*)getRenderable())->setNormal(getEngine()->getResourceLoader()->loadTexture(normalpath));
}

void GenericBackground::removed() {
	
}

void GenericBackground::update(float dt) {
	

}