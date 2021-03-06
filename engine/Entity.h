#pragma once

class Renderable;
class GraphicsContext;
class Collider;

#include "World.h"
#include "engine.h"
#include "windowing/window.h"
#include "math/Vector2.h"
#include "scripting/ScriptInstance.h"
#include <string>
#include <map>

enum class EntityState {
    PENDING_ADD,
    ACTIVE,
    PENDING_REMOVE,
    INVALID,
};

class Entity {
	friend class World;
public:
    Entity(Engine* engine);
    virtual ~Entity();

    World* getWorld();
    Engine* getEngine();

    void setRenderable(std::shared_ptr<Renderable> r);
    std::shared_ptr<Renderable> getRenderable() const;

    void setCollider(std::shared_ptr<Collider> r);
	std::shared_ptr<Collider> getCollider() const;

    void setState(EntityState state);
    EntityState getState() const;

    void render(GraphicsContext& gc);

    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);

	float getRotation() const;
	void setRotation(float rotation);

    Vector2& getPosition();
	void setPosition(const Vector2& vec);

    const std::string& getType() const;
	void setType(const std::string& t);
	
	void move(float x, float y);

    void addScript(std::string name);
    ScriptInstance* getScript(std::string name);
    void removeScript(std::string name);
	std::map<std::string, ScriptInstance*>& getScripts();

	void destroy();

	//collision functions
	void onCollide(Entity* e);
	void onMoveCollideX(Entity* e, float amount);
	void onMoveCollideY(Entity* e, float amount);

	void added();
	void destroyed();
    void update(float dt);

private:
    Engine* _engine;

    std::string _type;
	Vector2 _position;
	float _rotation;
    std::shared_ptr<Renderable> _renderable;
	std::shared_ptr<Collider> _collider;
    std::map<std::string, ScriptInstance*> _scripts;
    EntityState _state;
};