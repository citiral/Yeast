#ifndef BOXBOXSOLVER_H
#define BOXBOXSOLVER_H

#include "../BoxCollider.h"
#include <functional>

class BoxBoxSolver
{
private:
	BoxBoxSolver();
	virtual ~BoxBoxSolver();

public:
	static bool collides(const BoxCollider& b1, const BoxCollider& b2);
	static void resolveCollision(const BoxCollider& b1, const BoxCollider& b2, std::function<void(float)> xCallback, std::function<void(float)> yCallback);
};

#endif // BOXBOXSOLVER_H
