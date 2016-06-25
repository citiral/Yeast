#pragma once

#include <vector>
#include <memory>
#include <list>

class Entity;
class Engine;
class Light;
class GraphicsContext;

class World {
public:
    World(Engine* engine);
    virtual ~World();
	
	virtual void added() = 0;
	virtual void removed() = 0;

    virtual void update(float dt);
    virtual void renderComposite(GraphicsContext& gc);
	virtual void renderLighting(GraphicsContext& gc);

	Engine* getEngine() const;
	
	//adds an entity to the world
    void addEntity(std::shared_ptr<Entity> e);
    void addEntity(Entity* e);

    //removes the entity from the world
    void removeEntity(Entity* e);
    void removeEntity(std::shared_ptr<Entity> e);
	
	//adds a light to the world
    void addLight(Light* l);
    void addLight(std::shared_ptr<Light> l);

    //removes the light from the world
    void removeLight(Light* l);
    void removeLight(std::shared_ptr<Light> l);
	
	int getEntityCount() const;

    std::list<std::shared_ptr<Entity>>& getEntities();
    std::vector<std::shared_ptr<Light>>& getLights();

private:
    Engine* _engine;
    std::vector<std::shared_ptr<Light>> _lights;
    std::list<std::shared_ptr<Entity>> _entities;
};