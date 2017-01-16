#pragma once

#include <vector>
#include <memory>
#include <list>
#include "scripting/ScriptInstance.h"
#include "scripting/LuaIterator.h"

class Entity;
class Engine;
class Light;
class GraphicsContext;

class World {
public:
    World(Engine* engine, ScriptInstance* script);
    virtual ~World();
	
	void added();
	void removed();

    void update(float dt);
    void renderComposite(GraphicsContext& gc);
	void renderLighting(GraphicsContext& gc);

	Engine* getEngine() const;
	
	//adds an entity to the world
    void addEntity(Entity* e);

    //removes the entity from the world
    void destroyEntity(Entity* e);
	
	//adds a light to the world
    void addLight(Light* l);
    void addLight(std::shared_ptr<Light> l);

    //removes the light from the world
    void removeLight(Light* l);
    void removeLight(std::shared_ptr<Light> l);
	
	int getEntityCount() const;

	ScriptInstance* getScript();

    std::list<Entity*>& getEntities();
    LuaIterator<std::list<Entity*>::iterator> getEntitiesIterator();

    std::vector<std::shared_ptr<Light>>& getLights();
    LuaIterator<std::vector<std::shared_ptr<Light>>::iterator> getLightsIterator();
private:
    Engine* _engine;
    std::vector<std::shared_ptr<Light>> _lights;
    std::list<Entity*> _entities;
	ScriptInstance* _script;
};