#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "PhysicsComponent.h"
#include "Transform.h"

class Collider;
#ifndef USE_DIRECTXTK_MATH
struct BoundingBox;
#endif

class Rigidbody : public PhysicsComponent {
public:
	using PhysicsComponent::PhysicsComponent;
	~Rigidbody();


	void CreateCollider(const float radius);
	void CreateCollider(const DirectX::BoundingBox box);
	Collider* GetCollider() { return _collider; };

	void SetOffset(Transform offset) { _offsetTransform = offset; };
	
	void Start();
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

	float _restitution = 0.2f;
};

#endif