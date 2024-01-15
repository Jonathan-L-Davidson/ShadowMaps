#include "PhysicsComponent.h"
#include "Object.h"

void PhysicsComponent::Start() {
	
}

void PhysicsComponent::Update(float deltaTime) {
	if (m_velocity.Magnitude() != 0) {
		Vector3 pos = m_oldPos + (m_velocity * deltaTime);
		_owner->SetPosition(pos);
		m_oldPos = pos;
	}


}

void PhysicsComponent::Destroy() {
	
}

void PhysicsComponent::UpdatePhysics(float deltaTime) {
	
}
