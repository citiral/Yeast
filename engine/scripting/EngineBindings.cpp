//
// Created by Citiral on 6/07/2016.
//

#include "EngineBindings.h"
#include "../math/Vector2.h"
#include "../Entity.h"

void bind(LuaEngine* engine, lua_State* L) {
    engine->registerClass<Vector2>();
    engine->registerClass<Entity*>();
}