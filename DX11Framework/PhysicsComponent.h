#pragma once
#ifndef PHYSICS_COMP_H
#define PHYSICS_COMP_H

#include "Component.h"
#include "Physics/Vector3.h"
using namespace Physics;

class PhysicsComponent : Component
{
	public:
		void Start();
		void Update(float deltaTime);
		void Destroy();

	private:
		void UpdatePhysics(float deltaTime);

		Vector3 m_velocity;
		Vector3 m_forces;
		Vector3 m_acceleration;

		Vector3 m_oldPos;

		float m_maxSpeed = 10.0f;
};

#endif // !PHYSICS_COMP_H
