#include <engine.h>
#include "Settings.h"
#include <Timer.h>

int main() {
    Timer t;
    // for now let the framework just load the game dll, get the basic world entry
    Engine engine(1366, 768, false);
    engine.getSettings()->load("res\\settings.ini");
    engine.begin();
}