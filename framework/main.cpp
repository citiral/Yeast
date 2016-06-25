#include "engine.h"

int main() {
    // for now let the framework just load the game dll, get the basic world entry
    Engine engine(1366, 768, false);
    engine.begin(nullptr);
}