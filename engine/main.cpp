#include "engine.h"
#include "paths.h"

int main() {
    //std::cout << "hello world";
    std::string settingspath = formatPath("res/settings.ini");
    Engine engine(settingspath.c_str());
    engine.begin();

}