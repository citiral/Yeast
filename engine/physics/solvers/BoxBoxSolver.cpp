#include "BoxBoxSolver.h"
#include <cmath>


bool BoxBoxSolver::collides(const BoxCollider& b1, const BoxCollider& b2) {
	return	b1.getX() - b1.getOrigin().getX() < b2.getX() + b2.getWidth() - b2.getOrigin().getX() &&
			b1.getX() + b1.getWidth() - b1.getOrigin().getX() > b2.getX() - b2.getOrigin().getX() &&
			b1.getY() - b1.getOrigin().getY() < b2.getY() + b2.getHeight() - b2.getOrigin().getY() &&
			b1.getY() + b1.getHeight() - b1.getOrigin().getY() > b2.getY() - b2.getOrigin().getY();
}

void BoxBoxSolver::resolveCollision(const BoxCollider& b1, const BoxCollider& b2, std::function<void(float)> xCallback, std::function<void(float)> yCallback) {
	float interLeft = std::abs(b2.getX() - b2.getOrigin().getX() - (b1.getX() + b1.getWidth() - b1.getOrigin().getX()));
	float interRight = std::abs(b1.getX() - b1.getOrigin().getX() - (b2.getX() + b2.getWidth() - b2.getOrigin().getX())); 
	float interBottom = std::abs(b2.getY() - b2.getOrigin().getY() - (b1.getY() + b1.getHeight() - b1.getOrigin().getY()));
	float interTop = std::abs(b1.getY() - b1.getOrigin().getY() - (b2.getY() + b2.getHeight() - b2.getOrigin().getY()));
	
	if (interLeft < interRight && interLeft < interBottom && interLeft < interTop) {
		xCallback(-interLeft);
	} else if (interRight < interBottom && interRight < interTop) {
		xCallback(interRight);
	} else if (interTop < interBottom) {
		yCallback(interTop);
	} else {
		yCallback(-interBottom);
	}
}