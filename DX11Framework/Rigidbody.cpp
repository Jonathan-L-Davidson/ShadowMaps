#include "Debug.h"
#include "Rigidbody.h"
#include "Object.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "ObjectManager.h"

static int DebugPrintVector(const Vector3& vec, const char* prefix) {
	return DebugPrintF("%s: x - %f, y - %f, z - %f\n", prefix, vec.x, vec.y, vec.z);
}

Rigidbody::~Rigidbody() {
	PhysicsComponent::Destroy();
	delete _collider;
	delete _transform;
}

void Rigidbody::CreateCollider(const float radius) {
	_collider = new SphereCollider(radius);
}

void Rigidbody::CreateCollider(const BoundingBox box) {
	_collider = new BoxCollider(_transform, _offsetTransform, box);
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

		Vector3 normal = _collider->CollidesWith(*rb->GetCollider());
		normal.Normalise();
		if (!normal.IsZero()) { // Is there a collision normal? If so, collision.
			Vector3 relativeVelocity = rb->GetVelocity() - GetVelocity();

			float relativeDot = relativeVelocity.DotProduct(normal);
			if (relativeDot > 0) { // we're in the direction of colliding. 
				float totalVelocity = -(1 + _restitution) * relativeDot;

				float momentum = totalVelocity * GetInverseMass() + rb->GetInverseMass();

				AddImpulse(normal * GetInverseMass() * momentum);
				rb->AddImpulse((normal * rb->GetInverseMass() * momentum) * -1);
			}
			//DebugPrintF("Collision!!! %s hits %s\n", _owner->GetName().c_str(), rb->_owner->GetName().c_str());
			continue;
		}
	}
}

float Rigidbody::GetContactArea(const Vector3& direction) {
	return 1.0f; 
}