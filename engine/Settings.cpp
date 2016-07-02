//
// Created by Citiral on 30/06/2016.
//

#include <fstream>
#include <iostream>
#include "Settings.h"

Settings* Settings::_instance = nullptr;

Settings::Settings() {
}

Settings::~Settings() {
}

Settings* Settings::getInstance() {
    if (_instance == nullptr) {
        _instance = new Settings();
    }
    return _instance;
}

void Settings::load(std::string file) {
    std::string section = "default";

    std::fstream input;
    input.open(file);

    for (std::string line; std::getline(input, line);)  {
        size_t pos;
        // a section
        if (line.length() == 0) {
            continue;
        }
        else if (line[0] == '[' && line[line.length() - 1] == ']') {
            section = line.substr(1, line.length() - 2);
        }
            // skip comments
        else if (line[0] == '#') {
            continue;
        }
            // if the line contains an =, its a value
        else if ((pos = line.find('=')) != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos+1, std::string::npos);
            data[std::make_tuple(section, key)] = value;
        }
        else {
            std::cout << "in " << file << ": unknown line " << line;
        }
    }
}

bool Settings::has(std::string section, std::string key) {
    return data.find(std::make_tuple(section, key)) != data.end();
}

std::string Settings::get(std::string section, std::string key) {
    return data[std::make_tuple(section, key)];
}