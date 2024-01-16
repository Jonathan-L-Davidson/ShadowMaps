#pragma once
#ifndef PHYSICS_COMP_H
#define PHYSICS_COMP_H
#include <vector>

#include "Component.h"
#include "Physics/Vector3.h"
using namespace Physics;

class PhysicsComponent : public Component
{
	public:
		PhysicsComponent() {};
		PhysicsComponent
		(	const float mass,
			const float dragCoef,
			const bool useConstantVel) :
			mass(mass),
			dragCoef(dragCoef),
			useConstantVelocity(useConstantVel)
			{ };
		void Start();
		void Update(float deltaTime);
		void Destroy();

		void AddForce(const Vector3 force) { m_forces.push_back(force); };

		float mass = 10.0f;
		float dragCoef = 1.05f; // cube coeff
		bool useConstantVelocity = false;
	private:
		void UpdatePhysics(float deltaTime);
		void CalculateForces(float deltaTime);
		void CalculateAcceleration(float deltaTime);
		void CalculateVelocity(float deltaTime);

		void UpdatePosition(float deltatime);

		Vector3 m_velocity;
		Vector3 m_acceleration;
		Vector3 m_forceTotal;
		std::vector<Vector3> m_forces;

		Vector3 m_oldVelocity;
		Vector3 m_oldPos;

		float m_maxSpeed = 500.0f;
};

#endif // !PHYSICS_COMP_H
