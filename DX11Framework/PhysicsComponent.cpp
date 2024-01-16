#include "PhysicsComponent.h"
#include "Object.h"

void PhysicsComponent::Start() {
	
}

void PhysicsComponent::Update(float deltaTime) {
	for (Vector3 force : m_forces) {
		m_forceTotal += force;
	}

	m_acceleration += m_forceTotal;

	m_velocity += m_acceleration * deltaTime;

	if (m_velocity.Magnitude() != 0) {
		Vector3 pos = m_oldPos + (m_velocity * deltaTime);
		_owner->SetPosition(pos);
		m_oldPos = pos;
	}

	m_forceTotal = Vector3(); // Resets it by returning default values.
	m_forces.clear();
}

void PhysicsComponent::Destroy() {
	
}

void PhysicsComponent::UpdatePhysics(float deltaTime) {
	
}
