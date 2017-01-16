//
// Created by Olivier on 16/01/17.
//

#include "paths.h"

std::string formatPath(std::string path) {
    #if defined(_WIN32)

    // replace all forward slashes with backslashes
    for (auto c = path.begin() ; c != path.end() ; c++) {
        if (*c == '/')
            *c = '\\';
    }

    return path;

    #elif defined(__APPLE_CC__) || defined(BSD)
    // TODO
    return path;
    #elif defined(__linux__)
    // TODO
    return path;
    #endif
}