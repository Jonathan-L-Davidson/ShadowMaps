#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include "Collider.h"

struct BoundingBox {
	Vector3 points[8];

	Vector3 origin;
};

class BoxCollider : public Collider
{
public:
	BoxCollider(Transform* transform, Transform offsetTransform, BoundingBox box) : Collider(transform, offsetTransform) { _boxShape = box; };
	BoxCollider(Transform* transform, Transform offsetTransform) : Collider(transform, offsetTransform) { };
	BoxCollider(BoundingBox box) : Collider() { _boxShape = box; };

	void GenerateBoundingBox(Vector3 origin, float width, float length, float height);

	virtual bool CollidesWith(Collider& other) { return other.CollidesWith(*(BoxCollider*)this); };
	virtual bool CollidesWith(SphereCollider& other) override;
	virtual bool CollidesWith(BoxCollider& other) override;
	
	BoundingBox GetBox() { TranslateBox(); return _translatedBox; }
	void TranslateBox();


private:
	bool CollidesOnAxis(BoundingBox boxA, BoundingBox boxB, Vector3 axis);
	bool CollidesOnAxis(BoundingBox boxA, Vector3 spherePos, float sphereRadius);
	void GetMinMax(float& min, float& max, BoundingBox box, Vector3 axis);

	BoundingBox _boxShape;
	BoundingBox _translatedBox;

};


#endif