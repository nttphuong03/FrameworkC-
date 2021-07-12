#ifndef Collision_Manager_H
#define Collision_Manager_H
#include "Object.h"
class CollisionManager {
  public:
	 CollisionManager();
	~CollisionManager();
	bool areShapesColliding(Object* shape1, Object* shape2);
	bool areShapesColliding(RectangleShape* rect1, RectangleShape* rect2);
	bool areShapesColliding(CircleShape* circle1, CircleShape* circle2);
	bool areShapesColliding(CircleShape* circle, RectangleShape* rect);

};
#endif