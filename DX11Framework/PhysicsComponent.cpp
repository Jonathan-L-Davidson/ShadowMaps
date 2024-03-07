#include "Debug.h"
#include "Rigidbody.h"
#include "PhysicsComponent.h"
#include "Object.h"

void PhysicsComponent::Start() {
	_oldPos = _owner->transform->position;
}

void PhysicsComponent::Update(float deltaTime) {
	if (useGravity) {
		HandleGravity();
	}

	UpdatePhysics(deltaTime);
}

void PhysicsComponent::Destroy() {
	
}

void PhysicsComponent::HandleGravity() {
	if (_owner->GetPosition().y < 0 || _oldPos.y < 0) {
		_oldPos.y = 0;
		_owner->SetPosition(_oldPos);
		if (_velocity.y < 0) {
			_velocity.y = 0;
		}

		hasFriction = true;
	}
	else if (_owner->GetPosition().y > 0) {
		AddForce(gravity * mass);
		hasFriction = false;
	}
}

void PhysicsComponent::UpdatePhysics(float deltaTime) {
	UpdateLinearMotion(deltaTime);
	UpdateAngularMotion(deltaTime);

	_forceTotal = Vector3(); // Resets it by returning default values.
	_forces.clear();
	_impulses.clear();
	_acceleration = Vector3();

	_rotationalForces.clear();
	_rotationalForce = Vector3();
}

#pragma region Linear Motion
void PhysicsComponent::UpdateLinearMotion(float deltaTime) {
	CalculateForces(deltaTime);
	CalculateAcceleration(deltaTime);
	CalculateVelocity(deltaTime);
	UpdatePosition(deltaTime);
}

void PhysicsComponent::CalculateForces(float deltaTime) {
	for (Vector3 force : _forces) {
		_forceTotal += force;
	}

	HandleDrag();
	HandleFriction();
}

void PhysicsComponent::CalculateAcceleration(float deltaTime) {
	_acceleration += _forceTotal / mass;
}

void PhysicsComponent::CalculateVelocity(float deltaTime) {
	if (!useConstantAcceleration) {
		_velocity += _acceleration * deltaTime;
	}
	else {
		_velocity += _acceleration;
	}

	for (Vector3 impulse : _impulses) {
		_velocity += impulse;
	}
}

void PhysicsComponent::UpdatePosition(float deltaTime) {
	float magnitude = _velocity.Magnitude();

	if (magnitude > _maxSpeed) {
		_velocity.Normalise();
		_velocity *= _maxSpeed;
	}

	if (magnitude != 0) {
		Vector3 pos = _oldPos + (_velocity * (useConstantVelocity ? 1.0f : deltaTime));
		_owner->SetPosition(pos);
		_oldPos = pos;
	}

}

void PhysicsComponent::HandleDrag() {
	float velMagnitude = _velocity.SquareMagnitude();

	if (velMagnitude != 0) {
		//DebugPrintF("Velocity: %f \n", velMagnitude);
		if (useDrag) {
			Vector3 dragForce = _velocity * -1.0f;
			dragForce.Normalise();


			// turbulent
			Rigidbody* rb = _owner->GetComponent<Rigidbody>();
			if (useTurbulentDrag && rb != nullptr) {
				float force = (0.5f * (dragAmount * velMagnitude * dragCoef * rb->GetContactArea(dragForce)));
				dragForce *= force;
			}
			// laminar
			else if (useLaminarDrag || (!useTurbulentDrag && rb == nullptr)) {
				float force = (0.5f * (dragAmount * velMagnitude * dragCoef));
				dragForce *= force;
			}
			_forceTotal += dragForce;
		}
	}
}

void PhysicsComponent::HandleFriction() {
	float velMagnitude = _velocity.SquareMagnitude();


	if (hasFriction) {
		float friction = mass * gravity.Magnitude() * frictionCoef;

		Vector3 forceApplication = (_velocity * -1.0f) * friction;

		_forceTotal += forceApplication;

	}
}
#pragma endregion

#pragma region Angular Motion
void PhysicsComponent::UpdateAngularMotion(float deltaTime) {
	for (Vector3 force : _rotationalForces) {
		_rotationalForce += force;
	}

	_relativePosition = _owner->transform->position;

	Vector3 torque = _relativePosition.CrossProduct(_rotationalForce);


	// Inertia Tensor
	XMFLOAT3X3 inertia;
	XMStoreFloat3x3(&inertia, XMMatrixIdentity());

	// Slide 30 RigidBodies part 1:
	// (y^2 + z^2) * m * 1/12 for _11
	// (x^2 + z^2) * m * 1/12 for _22
	// (x^2 + y^2) * m * 1/12 for _33
	// unsure if correct

	// Assuming sphere to make calculations easier however, using the implementing quaternions and rotations)
	// _11, _22, _33 = 2/5 * m * r^2
	float inertiaDrag = 0.4f * mass * (radius * radius);
	inertia._11 = inertiaDrag;
	inertia._22 = inertiaDrag;
	inertia._33 = inertiaDrag;
	

	XMMATRIX inertiaTensor = XMLoadFloat3x3(&inertia); // Loading it into a matrix to be able to invert it.
	inertiaTensor = XMMatrixInverse(nullptr, inertiaTensor); // Inverting it.

	// Acceleration
	Vector3 _angularAcceleration = TransformToVector3(torque, inertiaTensor);

	// Velocity
	_angularVelocity += _angularAcceleration * deltaTime;

	// Dampening
	_angularVelocity *= pow(angularDampening, deltaTime);
	if (_angularVelocity.SquareMagnitude() != 0) {

		// Applies rotation
		_owner->transform->AddRotation(_angularVelocity * deltaTime);

		_owner->transform->rotation.Normalise();
		//DebugPrintF("Angular velocity = %f\n", _angularVelocity.SquareMagnitude());
	}

}
#pragma endregion