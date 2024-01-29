#include "Rigidbody.h"
#include "Object.h"
#include "Collider.h"
#include "SphereCollider.h"

Rigidbody::~Rigidbody() {
	PhysicsComponent::Destroy();
	delete _collider;
	delete _transform;
}

void Rigidbody::CreateCollider(const float radius) {
	_collider = new SphereCollider(_owner->transform, _offsetTransform, radius);
}

void Rigidbody::CreateCollider(const Cube& cube) {
	//_collider = new CubeCollider(_transform, _offsetTransform, cube);
}


void Rigidbody::Update(float deltaTime) {
	PhysicsComponent::Update(deltaTime);
	UpdateCollision();
}

void Rigidbody::UpdateCollision() {
	//Vector<Rigidbody*> _owner->GetObjManager()->GetCollisionBodies(*this);
	
	// for every rigidbody
	// check collision
	// if collision
	//	collisionHandle
	//
	// return
}

float Rigidbody::GetContactArea(const Vector3& direction) {
	return 1.0f; 
}