#include "ResourceManager.h"
#include "../paths.h"

#if defined(__linux__)
#include <dirent.h>
#include <cstring>

#endif
/*
#if defined(__linux__)
int listdir(const char *path) {
    struct dirent *entry;
    DIR *dp;

    dp = opendir(path);
    if (dp == NULL) {
        perror("opendir: Path does not exist or could not be read.");
        return -1;
    }

    while ((entry = readdir(dp)))
        puts(entry->d_name);

    closedir(dp);
    return 0;
}
#endif



*/

// depending on the platform, we need to recursively add watches in a platform dependant way
#if defined(_WIN32)
template<class T>
void ResourceManager::addWatch(std::string path, ResourceListener<T>* watch) {
    _fileWatcher->addWatch(formatPath(path), watch);
    _watches.push_back(path);
}
#elif defined(__APPLE_CC__) || defined(BSD)
#elif defined(__linux__)
template<class T>
void ResourceManager::addWatch(std::string path, ResourceListener<T>* watch) {
    path = formatPath(path);
    // first we add a watch to the current folder
    _fileWatcher->addWatch(path, watch);

    // we also register it to our list of watches
    _watches.push_back(path);

    // and then we loop over all subfolders, and add recursively watch them
    struct dirent* entry;
    DIR* dp;

    // first we open the current directory to loop over
    dp = opendir(path.c_str());

    // if we failed to open the current directory, just abort
    if (dp == NULL) {
        std::cerr << "failed opening " << path << " to add a file watch.";
        return;
    }

    // then iterate over all members of the folder
    while ((entry = readdir(dp))) {
        // if the entry is a folder, and not "." or ".."
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            // recurse over it
            addWatch(path + "/" + entry->d_name, watch);
        }
    }

    // and finally close the directory
    closedir(dp);
    return;
}
#endif


ResourceManager::ResourceManager(Engine* engine) {
    _engine = engine;
    _fileWatcher = new FW::FileWatcher();

    addWatch("res\\assets", new ResourceListener<GL30Texture>(&_textures, [this] (std::string& path, std::shared_ptr<GL30Texture> texture) {
        texture->hotSwap(path);
    }));

    addWatch("res\\scripts", new ResourceListener<Script>(&_scripts, [this] (std::string& path, std::shared_ptr<Script> script) {
        script->hotSwap(_engine, path);
    }));
}

ResourceManager::~ResourceManager() {
    for (std::string& watch : _watches)
        _fileWatcher->removeWatch(watch);
}

std::shared_ptr<Program> ResourceManager::loadProgram(const char* vertex, const char* fragment) {
    return _programs.getResource(std::make_pair(formatPath(FOLDER_SHADERS + std::string(vertex)), formatPath(FOLDER_SHADERS + std::string(fragment))));
}

std::shared_ptr<GL30Texture> ResourceManager::loadTexture(const char* path) {
    return _textures.getResource(formatPath(FOLDER_ASSETS + std::string(path)));
}
/*
std::shared_ptr<WorldBlueprint> ResourceManager::loadWorld(const char* path) {
    return _worlds.getResource(std::string(path));
}

std::shared_ptr<EntityBlueprint> ResourceManager::loadEntity(const char* path) {
    return _entities.getResource(std::string(path));
}*/

std::shared_ptr<Script> ResourceManager::loadScript(const char* path) {
    return _scripts.getResource(formatPath(FOLDER_SCRIPTS + std::string(path)));
}

std::shared_ptr<Program> ResourceManager::loadProgram(const std::string& vertex, const std::string& fragment) {
    return _programs.getResource(std::make_pair(formatPath(FOLDER_SHADERS + vertex), formatPath(FOLDER_SHADERS + fragment)));
}

std::shared_ptr<GL30Texture> ResourceManager::loadTexture(const std::string& path) {
    return _textures.getResource(formatPath(FOLDER_ASSETS + path));
}
/*
std::shared_ptr<WorldBlueprint> ResourceManager::loadWorld(const std::string& path) {
    return _worlds.getResource(path);
}

std::shared_ptr<EntityBlueprint> ResourceManager::loadEntity(const std::string& path) {
    return _entities.getResource(path);
}*/

std::shared_ptr<Script> ResourceManager::loadScript(const std::string& path) {
    return _scripts.getResource(formatPath(FOLDER_SCRIPTS + path));
}

FW::FileWatcher* ResourceManager::getFileWatcher() {
    return _fileWatcher;
}
