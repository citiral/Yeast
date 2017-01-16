#include "World.h"
#include "Entity.h"
#include "graphics/lighting/light.h"
#include "graphics/lighting/FullBrightLight.h"
#include "graphics/graphicscontext.h"
#include "graphics/lighting/FullBrightLight.h"
#include <algorithm>
#include <iostream>

World::World(Engine* engine, ScriptInstance* script):
    _engine(engine), _script(script) {
	//every world should have a fullbright light, so we add it here
	addLight(new FullBrightLight(engine));

    // and initialize the script
    _script->setValue("this", this);
}

World::~World() {
    // because the arrays are shared pointers, they will clean themselves up
}

void World::update(float dt) {
    // iterate over all entities
    auto iter = _entities.begin();
    while (iter != _entities.end()) {
        Entity* e = *iter;

        if (e->getState() == EntityState::INVALID) {
            std::cout << "Error encountered entity with invalid state.";
            ++iter;
        } else if (e->getState() == EntityState::PENDING_ADD) {
            // if the entity is pending adding, set its state and call the added function
            e->setState(EntityState::ACTIVE);
            e->added();
            ++iter;
        } else if (e->getState() == EntityState::PENDING_REMOVE) {
            // call the destroyed callback
            e->destroyed();
            // remove the current entity from the list
            iter = _entities.erase(iter);
        } else if (e->getState() == EntityState::ACTIVE) {
            e->update(dt);
            ++iter;
        }
    }
}

void World::renderComposite(GraphicsContext& gc) {
    for (Entity* e : _entities) {
        e->render(gc);
    }
}

void World::renderLighting(GraphicsContext& gc) {
    for (std::shared_ptr<Light>& l : _lights) {
        gc.drawLight(*l);
    }
}

void World::addEntity(Entity* e) {
    e->setState(EntityState::PENDING_ADD);
    _entities.push_back(e);
}

void World::destroyEntity(Entity* e) {
    e->setState(EntityState::PENDING_REMOVE);
}

void World::addLight(Light* l) {
    _lights.push_back(std::shared_ptr<Light>(l));
}

void World::addLight(std::shared_ptr<Light> l) {
    _lights.push_back(l);
}

void World::removeLight(Light* l) {
    for (auto iter = _lights.begin() ; iter != _lights.end() ; iter++) {
        if (l == (*iter).get()) {
            _lights.erase(iter);
            return;
        }
    }
}

void World::removeLight(std::shared_ptr<Light>  l) {
    _lights.erase(std::find(_lights.begin(), _lights.end(), l));
}

Engine* World::getEngine() const {
	return _engine;
}

int World::getEntityCount() const {
	return _entities.size();
}

std::list<Entity*>& World::getEntities() {
    return _entities;
}

LuaIterator<std::list<Entity*>::iterator> World::getEntitiesIterator() {
    return LuaIterator<std::list<Entity*>::iterator>(_entities.begin(), _entities.end());
}

std::vector<std::shared_ptr<Light>>& World::getLights() {
    return _lights;
}

LuaIterator<std::vector<std::shared_ptr<Light>>::iterator> World::getLightsIterator() {
    return LuaIterator<std::vector<std::shared_ptr<Light>>::iterator>(_lights.begin(), _lights.end());
}

void World::added() {
    _script->runFunction("begin");
}

void World::removed() {

}

ScriptInstance* World::getScript() {
    return _script;
}


