#include "SphereCollider.h"

bool SphereCollider::CollidesWith(SphereCollider& other) {
	float dist = Vector3(other.GetPosition() - GetPosition()).SquareMagnitude();
	if (dist < _radius) {
		return true;
	}

	return false;
}
