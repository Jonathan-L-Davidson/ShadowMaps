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
			const bool useConstantVel,
			const bool useConstantAcc) :
			mass(mass),
			dragCoef(dragCoef),
			useConstantVelocity(useConstantVel),
			useConstantAcceleration(useConstantAcc)
			{ };
		void Start();
		virtual void Update(float deltaTime);
		void Destroy();

		void AddForce(const Vector3 force, bool useMass = true) { m_forces.push_back(force * (useMass ? mass : 1)); };
		void AddRotationalForce(const Vector3 force, bool useMass = true) { m_rotationalForces.push_back(force * (useMass ? mass : 1)); };

		float mass = 1.0f;
		float dragAmount = 5.0f;
		float dragCoef = 3.05f; // cube coeff
		Vector3 gravity = Vector3(0, -9.81f, 0);

		bool useGravity = true;
		bool hasFriction = false;
		bool useConstantVelocity = false;
		bool useConstantAcceleration = false;

		bool useDrag = true;
		bool useTurbulentDrag = true;
		bool useLaminarDrag = false;
		
		float friction = 10.0f;
		float frictionCoef = 1.0f;
		

		float angularDampening = 0.5f;

private:
		void UpdatePhysics(float deltaTime);
		void UpdateLinearMotion(float delaTime);
		void UpdateAngularMotion(float deltaTime);
		
		void CalculateForces(float deltaTime);
		void CalculateAcceleration(float deltaTime);
		void CalculateVelocity(float deltaTime);
		void HandleGravity();
		void HandleMagnitude();

		void UpdatePosition(float deltatime);

		Vector3 m_velocity;
		Vector3 m_acceleration;
		Vector3 m_forceTotal;
		std::vector<Vector3> m_forces;

		Vector3 m_oldVelocity;
		Vector3 m_oldPos;

		float m_maxSpeed = 500.0f;

		Vector3 m_rotationalForce;
		Vector3 m_angularVelocity;
		std::vector<Vector3> m_rotationalForces;
};

#endif // !PHYSICS_COMP_H
