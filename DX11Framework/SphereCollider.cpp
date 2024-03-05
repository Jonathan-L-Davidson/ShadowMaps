#include "SphereCollider.h"
#include "BoxCollider.h"

Vector3 SphereCollider::CollidesWith(SphereCollider& other) {
	Vector3 dir = other.GetPosition() - GetPosition();
	float dist = dir.Magnitude(); // Magnitude cannot be squared due to accuracy issues.
	if (dist < (_radius)) {
		dir.Normalise();
		return dir;
	}

	return Vector3();
}

Vector3 SphereCollider::CollidesWith(BoxCollider& other) {
	return other.CollidesWith(*this);
}
