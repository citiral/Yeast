#include "resourceloader.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <glad/glad.h>

ResourceLoader::ResourceLoader() {
    _mapProgram = new std::map<std::pair<std::string, std::string>, Resource<Program>>();
	_mapTexture = new std::map<std::string, Resource<GL30Texture>>;
}
ResourceLoader::~ResourceLoader() {
    delete _mapProgram;
	delete _mapTexture;
}

unsigned int ResourceLoader::loadShader(const char *path, unsigned int type) {
    std::fstream file;
    file.open(path, std::fstream::in);

    if (file.is_open()) {
        std::vector<const char *> code;
        //load the file in
        while (!file.eof()) {
            char *temp = new char[512];
            file.getline(temp, 510);
			int readcount = file.gcount();
			//we don't need to replace on the last line
			if (temp[readcount - 1] == '\0') {
				temp[readcount - 1] = '\n';
				temp[readcount] = '\0';
			}
            code.push_back(temp);
        }

        //compile the shader
        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, code.size(), code.data(), nullptr);
        glCompileShader(shader);

		//BEGIN error checking
		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if(isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		 
			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, 0, &errorLog[0]);
		 
			// Provide the infolog in whatever manor you deem best.
			std::cout << "error compiling shader [" << path << "]: " << errorLog.data() << std::endl;
			// Exit with failure.
			glDeleteShader(shader); // Don't leak the shader.
		}
		//END error checking
		
        //delete the code
        for (auto it = code.begin(); it != code.end(); it++) {
            delete *it;
        }

        return shader;
    } else {
        std::cout << "file not found: " << path << "\n";
    }
    return 0;
}

Resource<Program> ResourceLoader::loadProgram(const std::string &vertex, const std::string &fragment) {
    auto element = _mapProgram->find(std::pair<std::string, std::string>(vertex, fragment));

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
    }
}

Resource<GL30Texture> ResourceLoader::loadTexture(const std::string& path) {
	auto element = _mapTexture->find(path);

    if (element != _mapTexture->end()) {
		return std::get<1>(*element);
    } else {
		Resource<GL30Texture> resource = Resource<GL30Texture>(new GL30Texture(path));

        _mapTexture->emplace(std::pair<std::string, Resource<GL30Texture>>(path, resource));

        return resource;
    }
}
