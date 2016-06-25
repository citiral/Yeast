#pragma once

#include <map>
#include <utility>
#include <string>
#include <memory>
#include "resource.h"
#include "graphics/primitives/program.h"
#include "graphics/primitives/texture.h"

class ResourceLoader {
public:
    ResourceLoader();
    ~ResourceLoader();

    Resource<Program> loadProgram(const std::string& vertex, const std::string& fragment);
	Resource<GL30Texture> loadTexture(const std::string& path);


private:
	//program loading helper function
    unsigned int loadShader(const char* path, unsigned int type);

	//meaning: vertex_path & fragment_path -> program_resource
	std::map<std::pair<std::string, std::string>, Resource<Program>>* _mapProgram;
	
	//meaning: path -> texture_resource
	std::map<std::string, Resource<GL30Texture>>* _mapTexture;
};