#include "Collider.h"
#include "SphereCollider.h"

bool Collider::CollidesWith(Collider& other) {
	return false;
}

bool Collider::CollidesWith(SphereCollider& other) {
	return false;
}
