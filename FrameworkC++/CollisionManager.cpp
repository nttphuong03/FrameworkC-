#include "CollisionManager.h"
#include <math.h>
#include <iostream>

using namespace std;
CollisionManager::CollisionManager() {

}

CollisionManager::~CollisionManager() {

}

bool CollisionManager::areShapesColliding(Object* shape1, Object* shape2) {
	CircleShape* c1 = dynamic_cast<CircleShape*>(shape1);
	CircleShape* c2 = dynamic_cast<CircleShape*>(shape2);
	RectangleShape* rect1 = dynamic_cast<RectangleShape*>(shape1);
	RectangleShape* rect2 = dynamic_cast<RectangleShape*>(shape2);

	//if shape1 is circle and shape2 is circle
	if (c1 != nullptr && c2 != nullptr) {
		return areShapesColliding(c1, c2);
	}
	if (rect1 != nullptr && rect2 != nullptr) {
		return areShapesColliding(rect1, rect2);
	}
	if (c1 != nullptr && rect2 != nullptr) {
		return areShapesColliding(c1, rect2);
	}
	return areShapesColliding(c2, rect1);
}
bool CollisionManager::areShapesColliding(RectangleShape* rect1, RectangleShape* rect2) {
	if (rect1->cx >= rect2->cx + rect2->width || rect2->cx >= rect1->cx + rect1->width) {
		return false;
	}
	if (rect1->cy >= rect2->cy + rect2->height || rect2->cy >= rect1->cy + rect1->height) {
		return false;
	}
	if (rect1->isClick) {
		rect2->drop = false;
	}
	else if (rect2->isClick) {
		rect1->drop = false;
	}
	else {
		rect1->drop = true;
		rect2->drop = true;
	}
	printf("\nrect %d collision rect %d", rect1->id, rect2->id);
	return true;
}
bool CollisionManager::areShapesColliding(CircleShape* circle1, CircleShape* circle2) {
	float distance = sqrt((circle1->cx - circle2->cx)*(circle1->cx - circle2->cx) + (circle1->cy - circle2->cy)*(circle1->cy - circle2->cy));
	if (distance < circle1->radius + circle2->radius) {
		printf("\ncircle %d collision circle %d", circle1->id, circle2->id);

		if (circle1->isClick) {
			circle2->drop = false;
		}
		else if (circle2->isClick) {
			circle1->drop = false;
		}
		else {
			circle1->drop = true;
			circle2->drop = true;
		}
		return true;
	}
	return false;
}

float findMax(float a, float b) {
	if(a>b) return a;
	return b;
}
float findMin(float a, float b) {
	if(a<b) return a;
	return b;
}
bool CollisionManager::areShapesColliding(CircleShape* circle, RectangleShape* rect) {

	float xn = findMax(rect->cx, findMin(circle->cx, rect->cx+rect->width));
	float yn = findMax(rect->cy, findMin(circle->cy, rect->cy + rect->height));
	
	float dx = xn - circle->cx;
	float dy = yn - circle->cy;

	if (dx*dx + dy*dy <= circle->radius*circle->radius) {
		printf("\ncircle %d collision rectange %d", circle->id, rect->id);
		
		if (rect->isClick) {
			circle->drop = false;
		}
		else if (circle->isClick) {
			rect->drop = false;
		}
		else {
			circle->drop = true;
			rect->drop = true;
		}
		return true;
	}
	return false;
}