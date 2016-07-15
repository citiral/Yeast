#include "World.h"
#include "Entity.h"
#include "graphics/lighting/light.h"
#include "graphics/lighting/FullBrightLight.h"
#include "graphics/graphicscontext.h"
#include "graphics/lighting/FullBrightLight.h"
#include <algorithm>
#include <iostream>

World::World(Engine* engine):
    _engine(engine) {
	//every world should have a fullbright light, so we add it here
	addLight(new FullBrightLight(engine));
}

World::~World() {
    // because the arrays are shared pointers, they will clean themselves up
}

void World::update(float dt) {
    // iterate over all entities
    auto iter = _entities.begin();
    while (iter != _entities.end()) {
        Entity* e = (*iter).get();

        if (e->getState() == EntityState::INVALID) {
            std::cout << "Error encountered entity with invalid state.";
            ++iter;
        } else if (e->getState() == EntityState::PENDING_ADD) {
            // if the entity is pending adding, set its state and call the added function
            e->setState(EntityState::ACTIVE);
            e->added();
            ++iter;
        } else if (e->getState() == EntityState::PENDING_REMOVE) {
            // call the removed callback
            e->removed();
            // remove the current entity from the list
            iter = _entities.erase(iter);
        } else if (e->getState() == EntityState::ACTIVE) {
            e->update(dt);
            ++iter;
        }
    }
}

void World::renderComposite(GraphicsContext& gc) {
    for (std::shared_ptr<Entity> e : _entities) {
        e->render(gc);
    }
}

void World::renderLighting(GraphicsContext& gc) {
    for (auto it = _lights.begin() ; it != _lights.end() ; it++) {
        gc.drawLight(**it);
    }
}

void World::addEntity(std::shared_ptr<Entity> e) {
    e->setState(EntityState::PENDING_ADD);
    _entities.push_back(e);
}

void World::addEntity(Entity* e) {
    e->setState(EntityState::PENDING_ADD);
    _entities.push_back(std::shared_ptr<Entity>(e));
}

void World::removeEntity(std::shared_ptr<Entity> e) {
    e->setState(EntityState::PENDING_REMOVE);
}

void World::removeEntity(Entity* e) {
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

std::list<std::shared_ptr<Entity>>& World::getEntities() {
    return _entities;
}

std::vector<std::shared_ptr<Light>>& World::getLights() {
    return _lights;
}

void World::added() {

}

void World::removed() {

}
