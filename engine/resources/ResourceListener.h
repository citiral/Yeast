//
// Created by Olivier on 15/01/17.
//
#include "../simplefilewatcher/FileWatcher.h"
#include "resourceloader.h"
#include "../paths.h"
#include <string>
#include <iostream>

#ifndef YEAST_RESOURCELISTENER_H
#define YEAST_RESOURCELISTENER_H

template<class T>
class ResourceListener : public FW::FileWatchListener {
public:
    ResourceListener(ResourceLoader<std::string, T>* loader, std::function<void(std::string& path, std::shared_ptr<T> value)> callback) {
        _loader = loader;
        _callback = callback;
    }

    virtual void handleFileAction(FW::WatchID watchid, const std::string& dir, const std::string& filename, FW::Action action) {
        // we respond to both modified and added commands
        if (action != FW::Actions::Delete) {
            return;
        }

        // get the platform path to the asset
        std::string path = formatPath(dir + "\\" + filename);

        // and run the callback if the asset is currently loaded
        if (_loader->hasResource(path)) {
            _callback(path, _loader->getResource(path));
        }
    }

private:
    ResourceLoader<std::string, T>* _loader;
    std::function<void(std::string& path, std::shared_ptr<T> value)> _callback;
};


#endif //YEAST_RESOURCELISTENER_H
