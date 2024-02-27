#include "SphereCollider.h"
#include "BoxCollider.h"

bool SphereCollider::CollidesWith(SphereCollider& other) {
	float dist = Vector3(other.GetPosition() - GetPosition()).SquareMagnitude();
	if (dist < _radius) {
		return true;
	}

	return false;
}

bool SphereCollider::CollidesWith(BoxCollider& other) {
	return other.CollidesWith(*this);
}
