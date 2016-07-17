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

    std::list<std::shared_ptr<Entity>>& getEntities();
    std::vector<std::shared_ptr<Light>>& getLights();

private:
    Engine* _engine;
    std::vector<std::shared_ptr<Light>> _lights;
    std::list<std::shared_ptr<Entity>> _entities;
};