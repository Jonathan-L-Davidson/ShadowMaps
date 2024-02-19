#pragma once
#include "Collider.h"

struct BoundingBox {
	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

	Vector3 origin;
};

class BoxCollider : public Collider
{
public:
	BoxCollider(Transform* transform, Transform offsetTransform, BoundingBox box) : Collider(transform, offsetTransform) { _boxShape = box; };
	BoxCollider(Transform* transform, Transform offsetTransform) : Collider(transform, offsetTransform) { };
	BoxCollider(BoundingBox box) : Collider() { _boxShape = box; };

	void GenerateBoundingBox(Vector3 origin, float radiusX, float radiusY, float radiusZ);

	virtual bool CollidesWith(Collider& other) override { return other.CollidesWith(*this); };
	virtual bool CollidesWith(SphereCollider& other) override;
	virtual bool CollidesWith(BoxCollider& other);

private:
	BoundingBox _boxShape;

	void GenerateBoundingBox();
	void SeperatedAxisTheorum();
};

void BoxCollider::GenerateBoundingBox(Vector3 origin, float radiusX, float radiusY, float radiusZ) {
	BoundingBox box;

	box.minX = -radiusX + origin.x;
	box.maxX = radiusX + origin.x;
	
	box.minY = -radiusY + origin.y;	
	box.maxY = radiusY + origin.y;

	box.minZ = -radiusZ + origin.z;	
	box.maxZ = radiusZ + origin.z;

}
