
#ifndef COLLIDER_H
#define COLLIDER_H
#include "Transform.h"

class SphereCollider;

class Collider abstract {
public:
	Transform* _tf;
	Transform _offsetTransform;

	Collider(Transform* transform, Transform offsetTransform) { _tf = transform; _offsetTransform = offsetTransform; };
	Collider() { };

	virtual bool CollidesWith(Collider& other);
	virtual bool CollidesWith(SphereCollider& other);


	Vector3 GetPosition() const { return (*_tf + _offsetTransform).GetPosition(); };

};

#endif // !COLLIDER_H
