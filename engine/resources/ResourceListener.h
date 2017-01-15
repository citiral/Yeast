//
// Created by Olivier on 15/01/17.
//
#include "../simplefilewatcher/FileWatcher.h"
#include "resourceloader.h"
#include <string>
#include <iostream>

#ifndef YEAST_RESOURCELISTENER_H
#define YEAST_RESOURCELISTENER_H

template<class T>
class ResourceListener : public FW::FileWatchListener {
public:
    ResourceListener(ResourceLoader<std::string, T>* loader) {
        _loader = loader;
    }

    virtual void handleFileAction(FW::WatchID watchid, const std::string& dir, const std::string& filename, FW::Action action) {
        // we are only interested in modified files
        if (action != FW::Actions::Modified)
            return;

        std::string path = dir + "\\" + filename;

        std::cout << "File (" << path << ") Modified! " << std::endl;

        if (_loader->hasResource(path)) {
            std::cout << "reloading file" << std::endl;
            _loader->getResource(path)->hotSwap(path);
        } else {

            std::cout << "file is not found" << std::endl;
        }
    }

private:
    ResourceLoader<std::string, T>* _loader;
};


#endif //YEAST_RESOURCELISTENER_H
