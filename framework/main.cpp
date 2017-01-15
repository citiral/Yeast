#include <engine.h>

int main() {
    //std::cout << "hello world";
    // for now let the framework just load the game dll, get the basic world entry
    Engine engine("res\\settings.ini");
    engine.begin();

}