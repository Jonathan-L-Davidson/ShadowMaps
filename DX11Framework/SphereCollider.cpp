#include "SphereCollider.h"
#include "BoxCollider.h"

Vector3 SphereCollider::CollidesWith(SphereCollider& other) {
	Vector3 dir = other.GetPosition() - GetPosition();
	float dist = dir.Length(); // Magnitude cannot be squared due to accuracy issues.
	if (dist < (_radius)) {
		return dir;
	}

	return Vector3::Zero;
}

Vector3 SphereCollider::CollidesWith(BoxCollider& other) {
	return other.CollidesWith(*this);
}
