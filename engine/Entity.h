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

#define WINDOW getWorld()->getEngine()->getWindow()

enum class EntityState {
    PENDING_ADD,
    ACTIVE,
    PENDING_REMOVE,
    INVALID,
};

class Entity {
	friend class World;
public:
    Entity(Engine* engine, float x = 0, float y = 0, Renderable* renderable = nullptr);
    virtual ~Entity();

    World* getWorld();
    Engine* getEngine();

    void setRenderable(Renderable* r);
    Renderable* getRenderable() const;

    void setCollider(Collider* r);
    Collider* getCollider() const;

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
	void setPosition(float x, float y);

    const std::string& getType() const;
	void setType(const std::string& t);
	
	void moveTo(float x, float y);

    void addScript(ScriptInstance* script);

	//collision functions
	void onCollide(Entity* e);
	void onMoveCollideX(Entity* e, float amount);
	void onMoveCollideY(Entity* e, float amount);

	void added();
	void removed();
    void update(float dt);

private:
    Engine* _engine;

    std::string _type;
	Vector2 _position;
	float _rotation;
    Renderable* _renderable;
	Collider* _collider;
    std::vector<ScriptInstance*> _scripts;
    EntityState _state;
};