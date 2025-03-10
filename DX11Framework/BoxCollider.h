#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include "Collider.h"

// Not happy with how this is done, didn't expect DirectX to have BoundingBox and BoundingSpheres, woops!
#ifndef USE_DIRECTXTK_MATH
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

	virtual Vector3 CollidesWith(Collider& other) { return other.CollidesWith(*(BoxCollider*)this); };
	virtual Vector3 CollidesWith(SphereCollider& other) override;
	virtual Vector3 CollidesWith(BoxCollider& other) override;
	
	BoundingBox GetBox() { TranslateBox(); return _translatedBox; }
	void TranslateBox();


private:
	Vector3 CollidesOnAxis(BoundingBox boxA, BoundingBox boxB, Vector3 axis);
	Vector3 CollidesOnAxis(BoundingBox boxA, Vector3 spherePos, float sphereRadius);
	Vector3 GetMinMax(float& min, float& max, BoundingBox box, Vector3 axis);

	BoundingBox _boxShape;
	BoundingBox _translatedBox;

};
#else
class BoxCollider : public Collider
{
public:
	BoxCollider(Transform* transform, Transform offsetTransform, DirectX::BoundingBox box) : Collider(transform, offsetTransform) { _boxShape = box; };
	BoxCollider(Transform* transform, Transform offsetTransform) : Collider(transform, offsetTransform) { };
	BoxCollider(DirectX::BoundingBox box) : Collider() { _boxShape = box; };

	void GenerateBoundingBox(Vector3 origin, float width, float length, float height);

	virtual Vector3 CollidesWith(Collider& other) { return other.CollidesWith(*(BoxCollider*)this); };
	virtual Vector3 CollidesWith(SphereCollider& other) override;
	virtual Vector3 CollidesWith(BoxCollider& other) override;

	DirectX::BoundingBox GetBox() { TranslateBox(); return _translatedBox; }
	void TranslateBox();


private:
	Vector3 CollidesOnAxis(DirectX::BoundingBox boxA, DirectX::BoundingBox boxB, Vector3 axis);
	Vector3 CollidesOnAxis(DirectX::BoundingBox boxA, Vector3 spherePos, float sphereRadius);
	Vector3 GetMinMax(float& min, float& max, DirectX::BoundingBox box, Vector3 axis);

	DirectX::BoundingBox _boxShape;
	DirectX::BoundingBox _translatedBox;

};
#endif

#endif