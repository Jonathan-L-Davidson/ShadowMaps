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

		void AddForce(const Vector3 force, bool useMass = true) { _forces.push_back(force * (useMass ? mass : 1)); };
		void AddImpulse(const Vector3 force) { _impulses.push_back(force); };
		void AddRotationalForce(const Vector3 force, bool useMass = true) { _rotationalForces.push_back(force * (useMass ? mass : 1)); };

		Vector3 GetVelocity() { return _velocity; };
		float GetInverseMass() { return -(1 / mass); };

		float mass = 5.0f;
		float radius = 2.0f;
		float dragAmount = 1.2f;
		float dragCoef = 1.05f; // cube coeff
		Vector3 gravity = Vector3(0, -9.81f, 0);

		bool useGravity = true;
		bool hasFriction = true;
		bool useConstantVelocity = false;
		bool useConstantAcceleration = false;

		bool useDrag = true;
		bool useTurbulentDrag = false;
		bool useLaminarDrag = true;
		
		float frictionCoef = 0.2f;

		float angularDampening = 0.5f;

private:
		void UpdatePhysics(float deltaTime);
		void UpdateLinearMotion(float delaTime);
		void UpdateAngularMotion(float deltaTime);
		
		void CalculateForces(float deltaTime);
		void CalculateAcceleration(float deltaTime);
		void CalculateVelocity(float deltaTime);
		void HandleGravity();
		void HandleDrag();
		void HandleFriction();

		void UpdatePosition(float deltatime);

		Vector3 _velocity;
		Vector3 _acceleration;
		Vector3 _forceTotal;
		std::vector<Vector3> _forces;
		std::vector<Vector3> _impulses;

		Vector3 _oldVelocity;
		Vector3 _oldPos;

		float	_maxSpeed = 500.0f;
		Vector3 _relativePosition;


		Vector3 _rotationalForce;
		Vector3 _angularVelocity;
		std::vector<Vector3> _rotationalForces;
};

#endif // !PHYSICS_COMP_H
