//
// Created by Olivier on 01/08/16.
//

#include "Project.h"

Project::Project(QString location): _location(location) {
    if (!_location.endsWith('/')) {
        _location += '/';
    }
}

const QString& Project::getLocation() const {
    return _location;
}

