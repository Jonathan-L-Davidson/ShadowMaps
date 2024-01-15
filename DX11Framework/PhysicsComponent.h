#pragma once
#ifndef PHYSICS_COMP_H
#define PHYSICS_COMP_H
#include <vector>

#include "Component.h"
#include "Physics/Vector3.h"
using namespace Physics;

class PhysicsComponent : Component
{
	public:
		PhysicsComponent(const float mass, const float dragCoef) : _mass(mass), _dragCoef(dragCoef) { };
		void Start();
		void Update(float deltaTime);
		void Destroy();

	private:
		void UpdatePhysics(float deltaTime);
		float _mass;
		float _dragCoef;

		Vector3 m_velocity;
		Vector3 m_acceleration;
		Vector3 m_forceTotal;
		std::vector<Vector3> m_forces;

		Vector3 m_oldPos;

		float m_maxSpeed = 10.0f;
};

#endif // !PHYSICS_COMP_H
