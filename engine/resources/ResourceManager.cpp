#include "ResourceManager.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <glad/glad.h>

ResourceManager::ResourceManager() {
}
ResourceManager::~ResourceManager() {
}



Resource<Program> ResourceManager::loadProgram(const std::string &vertex, const std::string &fragment) {
    return _programs.getResource(std::make_pair(vertex, fragment));
    /*auto element = _mapProgram->find(std::pair<std::string, std::string>(vertex, fragment));

    if (element != _mapProgram->end()) {
        return std::get<1>(*element);
    } else {
        unsigned int vertexShader = loadShader(vertex.c_str(), GL_VERTEX_SHADER);
        unsigned int fragmentShader = loadShader(fragment.c_str(), GL_FRAGMENT_SHADER);

        Resource<Program> program_res = Resource<Program>(new Program(vertexShader, fragmentShader));

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        _mapProgram->emplace(std::pair<std::pair<std::string, std::string>, Resource<Program>>(std::pair<std::string, std::string>(vertex, fragment), program_res));

        return program_res;
    }*/
}

Resource<GL30Texture> ResourceManager::loadTexture(const std::string& path) {
    return _textures.getResource(path);
}