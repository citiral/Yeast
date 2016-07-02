//
// Created by Citiral on 30/06/2016.
//

#ifndef I_WANNA_KILL_THE_BOSHY_SETTINGS_H
#define I_WANNA_KILL_THE_BOSHY_SETTINGS_H

#include "Result.h"
#include <map>
#include <tuple>
#include <string>
#include <sstream>

class Settings
{
public:
    Settings();
    ~Settings();

    static Settings* getInstance();

    // initialisation functions
    void load(std::string file);

    // data fetching functions
    bool has(std::string section, std::string key);
    std::string get(std::string section, std::string key);

    template <class T>
    T getT(std::string section, std::string key) {
        std::stringstream str(data[std::make_tuple(section, key)]);
        T t;
        str >> t;
        return t;
    }

private:
    std::map<std::tuple<std::string, std::string>, std::string> data;

    static Settings* _instance;
};

#endif //I_WANNA_KILL_THE_BOSHY_SETTINGS_H
