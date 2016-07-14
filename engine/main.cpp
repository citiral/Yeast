#include "engine.h"
#include "Settings.h"
#include "resources/ResourceManager.h"
#include "scripting/LuaEngine.h"

int main() {
    // for now let the framework just load the game dll, get the basic world entry
    Engine engine(1366, 768, false);
    engine.getSettings()->load("res\\settings.ini");

    /*ScriptInstance* instance1 = engine.getResourceManager()->loadScript("res/scripts/mouselook.lua")->createInstance(&engine);
    ScriptInstance* instance2 = engine.getResourceManager()->loadScript("res/scripts/mouselook.lua")->createInstance(&engine);
    instance1->setValue("kaas", 2.23);
    instance2->setValue("kaas", 69);
    instance1->runFunction("update");
    instance2->runFunction("update");
    delete instance1;
    delete instance2;*/

    engine.begin();

}