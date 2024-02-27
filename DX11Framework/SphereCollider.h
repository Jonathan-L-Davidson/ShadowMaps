#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H
#include "Collider.h"

class SphereCollider : public Collider {
public:
	SphereCollider(Transform* transform, Transform offsetTransform, float radius) : Collider(transform, offsetTransform) { _radius = radius; };
	SphereCollider(float radius) : Collider() { _radius = radius; };

	float GetRadius() const { return _radius; };

	virtual bool CollidesWith(Collider& other) override { return other.CollidesWith(*this); };
	virtual bool CollidesWith(SphereCollider& other) override;
	virtual bool CollidesWith(BoxCollider& other) override;
private:
	float _radius = 1.0f;
};

#endif // !SPHERECOLLIDER_H
