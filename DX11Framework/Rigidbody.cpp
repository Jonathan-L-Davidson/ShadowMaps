#include "Debug.h"
#include "Rigidbody.h"
#include "Object.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "ObjectManager.h"

Rigidbody::~Rigidbody() {
	PhysicsComponent::Destroy();
	delete _collider;
	delete _transform;
}

void Rigidbody::CreateCollider(const float radius) {
	_collider = new SphereCollider(radius);
}

void Rigidbody::CreateCollider(const Cube& cube) {
	//_collider = new CubeCollider(_transform, _offsetTransform, cube);
}

void Rigidbody::Start() {
	PhysicsComponent::Start();
	if (_owner == nullptr) {
		throw new std::exception("Rigidbody woke without an object assigned!");
		return;
	}
	_collider->_tf = _owner->transform;
	_collider->_offsetTransform = _offsetTransform;
	_owner->GetObjManager()->AddCollisionBody(this);
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

	std::vector<Rigidbody*> rbList = _owner->GetObjManager()->GetBodies();

	for (Rigidbody* rb : rbList) {
		if (rb == this)	continue;

		if (_collider->CollidesWith(*rb->GetCollider())) {
			// handleCollision
			DebugPrintF("Collision!!! %s hits %s\n", _owner->GetName().c_str(), rb->_owner->GetName().c_str());
			return;
		}
		return;
	}
}

float Rigidbody::GetContactArea(const Vector3& direction) {
	return 1.0f; 
}