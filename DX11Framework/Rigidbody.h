#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "PhysicsComponent.h"
#include "Transform.h"

class Collider;
class Cube;

class Rigidbody : public PhysicsComponent {
public:
	using PhysicsComponent::PhysicsComponent;
	~Rigidbody();


	void CreateCollider(const float radius);
	void CreateCollider(const Cube& cube);

	void SetOffset(Transform offset) { _offsetTransform = offset; };
	
	void Update(float deltaTime);
	void UpdateCollision();

	/// <summary>
	/// Returns the area of the face the direction is facing in.
	/// </summary>
	/// <param name="direction"></param>
	/// <returns></returns>
	float GetContactArea(const Vector3& direction);
private:
	Collider* _collider;
	Transform* _transform;
	Transform _offsetTransform;

};

#endif