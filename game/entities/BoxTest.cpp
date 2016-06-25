#include "BoxTest.h"
#include "../../engine/physics/BoxCollider.h"

BoxTest::BoxTest(Engine* engine, bool moveable): Entity(engine)
{
	_moveable = moveable;

}

BoxTest::~BoxTest()
{
}


void BoxTest::added()
{
	/*GL30Texture* tex;
	if (_moveable) {
		tex = new GL30Texture("res/assets/box1.png");
		other = new BoxTest(false);
		getWorld()->addEntity(other);
	} else {
		tex = new GL30Texture("res/assets/box2.png");
		setX(800);
		setY(160);
	}
	
	setRenderable(tex);*/
	
	BoxCollider* collider = new BoxCollider(500, 500);
	
	setCollider(collider);
}

void BoxTest::removed()
{
}

void BoxTest::onMoveCollideX(Entity* e, float amount) {
	setX(getX() + amount);
}
	
void BoxTest::onMoveCollideY(Entity* e, float amount) {
	setY(getY() + amount);
}

void BoxTest::update(float dt)
{
	if (_moveable) {
		moveTo(WINDOW->getMouseX(), WINDOW->getMouseY());
	}
}
