#include "Debug.h"
#include "Rigidbody.h"
#include "PhysicsComponent.h"
#include "Object.h"

void PhysicsComponent::Start() {
	m_oldPos = _owner->transform->position;
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
	if (_owner->GetPosition().y < 0) {
		Vector3 pos = _owner->transform->position;
		pos.y = 0;
		_owner->SetPosition(pos);
		if (m_velocity.y < 0) {
			m_velocity.y = 0;
		}

		//hasFriction = true;
	}
	else if (_owner->GetPosition().y > 0) {
		AddForce(gravity * mass);
		hasFriction = false;
	}
}

void PhysicsComponent::UpdatePhysics(float deltaTime) {
	UpdateLinearMotion(deltaTime);
	UpdateAngularMotion(deltaTime);

	m_forceTotal = Vector3(); // Resets it by returning default values.
	m_forces.clear();
	m_acceleration = Vector3();

	m_rotationalForces.clear();
	m_rotationalForce = Vector3();
}

#pragma region Linear Motion

void PhysicsComponent::UpdateLinearMotion(float deltaTime) {
	CalculateForces(deltaTime);
	CalculateAcceleration(deltaTime);
	CalculateVelocity(deltaTime);
	UpdatePosition(deltaTime);
	HandleMagnitude();
}

void PhysicsComponent::CalculateForces(float deltaTime) {
	for (Vector3 force : m_forces) {
		m_forceTotal += force;
	}

	float velMagnitude = m_velocity.SquareMagnitude();

	// handle drag:
	if (velMagnitude != 0) {
		//DebugPrintF("Velocity: %f \n", velMagnitude);
		if (useDrag) {
			Vector3 dragForce = m_velocity;
			dragForce.Normalise();


			// turbulent
			Rigidbody* rb = _owner->GetComponent<Rigidbody>();
			if (useTurbulentDrag && rb != nullptr) {
				float force = (0.5f * (dragAmount * velMagnitude * dragCoef * rb->GetContactArea(dragForce)));
				dragForce *= force;
			}
			// laminar
			else if (useLaminarDrag) {
				float force = (0.5f * (dragAmount * velMagnitude * dragCoef));
				dragForce *= force;
			}

			dragForce *= -1;
			// DebugPrintF("dragForce = X: %f,Y: %f, Z: %z \n m_velocity = X: %f, Y: %f, Z: %f \n", dragForce.x, dragForce.y, dragForce.z, m_velocity.x, m_velocity.y, m_velocity.z);
			m_forceTotal += dragForce;
		}
	}

	// handle friction:
	if (hasFriction) {
		Vector3 forceApplication = m_forceTotal;
		forceApplication.Normalise();

		// Use calculation once
		// if it's static, then don't apply momentum.
		// if not, add the friction force.


		// kinetic friction
		if (velMagnitude > (friction * frictionCoef)) {
			forceApplication *= (friction * mass) * frictionCoef;
			//forceApplication *= -1;

			m_forceTotal += forceApplication;
		}
		// static friction
		else {
			if (m_forceTotal.SquareMagnitude() < friction) {
				m_forceTotal = Vector3(); // we apply no more forces.

				if (velMagnitude != 0) {
					m_velocity -= m_velocity / ((friction * mass) * frictionCoef); // this is cheating, I know.
				}
			}
		}
	}
}

void PhysicsComponent::CalculateAcceleration(float deltaTime) {
	if (!useConstantAcceleration) {
		m_acceleration += (m_forceTotal / mass) * deltaTime;
	}
	else {
		m_acceleration += m_forceTotal / mass;
	}
}

void PhysicsComponent::CalculateVelocity(float deltaTime) {
	if (!useConstantVelocity) {
		m_velocity += m_acceleration * deltaTime;
	}
	else {
		m_velocity += m_acceleration;
	}
}

void PhysicsComponent::UpdatePosition(float deltaTime) {
	float magnitude = m_velocity.Magnitude();

	if (magnitude > m_maxSpeed) {
		m_velocity.Normalise();
		m_velocity *= m_maxSpeed;
	}

	if (magnitude != 0) {
		Vector3 pos = m_oldPos + (m_velocity * deltaTime);
		_owner->SetPosition(pos);
		m_oldPos = pos;
	}

}

void PhysicsComponent::HandleMagnitude() {
	// idk how to calculate the magnitude :(
	// I need to think of how this works. It might be m_force_total realistically, before acceleration is applied.
	// no idea.
}

#pragma endregion

#pragma region Angular Motion
void PhysicsComponent::UpdateAngularMotion(float deltaTime) {
	// Calculate torque
	
	for (Vector3 force : m_rotationalForces) {
		m_rotationalForce += force;
	}

	// I don't know what relative position is in terms of how this rigidbody physics works so I'm setting it to be the position of the object.
	m_relativePosition = _owner->transform->position;

	Vector3 torque = m_relativePosition.CrossProduct(m_rotationalForce);


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
	Vector3 m_angularAcceleration = TransformToVector3(torque, inertiaTensor);

	// Velocity
	m_angularVelocity += m_angularAcceleration * deltaTime;

	// Dampening
	m_angularVelocity *= pow(angularDampening, deltaTime);
	if (m_angularVelocity.SquareMagnitude() != 0) {

		// Applies rotation
		_owner->transform->AddRotation(m_angularVelocity * deltaTime);

		_owner->transform->rotation.Normalise();
		//DebugPrintF("Angular velocity = %f\n", m_angularVelocity.SquareMagnitude());
	}

}
#pragma endregion