#pragma once

#include "resource.h"
#include <map>
#include <fstream>


template<class K, class T>
class ResourceLoader {
public:
    ResourceLoader();
    ~ResourceLoader();

    std::shared_ptr<T> getResource(const K& key);

    void destroyUnused();
private:
    std::map<K, std::shared_ptr<T>> _data;
};



template<class K, class T>
ResourceLoader<K, T>::ResourceLoader() {

}

template<class K, class T>
ResourceLoader<K, T>::~ResourceLoader() {
    // no need to manually clean up the resources since they do that themselves
}

template<class K, class T>
std::shared_ptr<T> ResourceLoader<K, T>::getResource(const K& key) {
    // if we already have the element, return it
    auto element = _data.find(key);
    if (element != _data.end()) {
        return std::get<1>(*element);
    } else {
        // generate a resource with that key
        std::shared_ptr<T> resource = std::make_shared<T>(key);
        _data.emplace(std::pair<K, std::shared_ptr<T>>(key, resource));
        return resource;
    }
}

// TODO: implement this
/*void ResourceLoader::destroyUnused() {

}*/
