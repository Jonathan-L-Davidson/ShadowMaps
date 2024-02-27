
#ifndef COLLIDER_H
#define COLLIDER_H
#include "Transform.h"

class SphereCollider;
class BoxCollider;

class Collider abstract {
public:
	Transform* _tf;
	Transform _offsetTransform;

	Collider(Transform* transform, Transform offsetTransform) { _tf = transform; _offsetTransform = offsetTransform; };
	Collider() { };

	virtual bool CollidesWith(Collider& other) = 0;
	virtual bool CollidesWith(SphereCollider& other) = 0;
	virtual bool CollidesWith(BoxCollider& other) = 0;


	Vector3 GetPosition() const { return (*_tf + _offsetTransform).GetPosition(); };

};


//bool Intersects(Vector3 pointA, Vector3 pointB, Vector3 plane) {
//	Vector3 vector = pointB - pointA;
//
//	x = 
//}


#endif // !COLLIDER_H
