#include "PhysicsComponent.h"
#include "Object.h"

void PhysicsComponent::Start() {
	m_oldPos = _owner->transform->position;
}

void PhysicsComponent::Update(float deltaTime) {
	UpdatePhysics(deltaTime);
}

void PhysicsComponent::CalculateForces(float deltaTime) {
	for (Vector3 force : m_forces) {
		m_forceTotal += force;
	}
}

void PhysicsComponent::CalculateAcceleration(float deltaTime) {
	m_acceleration += m_forceTotal;
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

void PhysicsComponent::Destroy() {
	
}

void PhysicsComponent::UpdatePhysics(float deltaTime) {
	CalculateForces(deltaTime);
	CalculateAcceleration(deltaTime);
	CalculateVelocity(deltaTime);
	UpdatePosition(deltaTime);

	m_forceTotal = Vector3(); // Resets it by returning default values.
	m_forces.clear();

}
