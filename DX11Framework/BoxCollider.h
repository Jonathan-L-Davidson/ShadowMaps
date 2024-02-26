#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include "Collider.h"

struct BoundingBox {
	Vector3 points[8];

	Vector3 origin;
};



// https://code.tutsplus.com/collision-detection-using-the-separating-axis-theorem--gamedev-169t
// Seperating axis theorom
// 
// Premise goes by seperating each value and comparing the X value
// 
// Checks the seperation on the X axis:
// l = magnitude((box2.position.x + box2.origin.x) - (box1.position + box1.origin.x))
// gap check by doing:
// 
// gapcheck = l - (box1.width * 0.5) - (box2.width * 0.5)
// 
// if the gap is less than or equal to 0 then there is a collision on the X axis.
// Do the same to all other axes.
// 
// To align, we just need to project these onto the axis we want.
// 
// But to do a 3D check, it'll look like:
// 
// vecDist = (box2.position + box2.origin) - (box1.position + box1.origin))
// 
// Then we get the vector to the points of the cube.
// 
// box1ToPoint = box1.p1 - box1.position
// box2ToPoint = box2.p1 - box2.position
// 
// projectedDist = vecDist.dot(axis)
// projectedBox1 = box1ToPoint.dot(axis)
// projectedBox2 = box2ToPoint.dot(axis)
//
// gap = projectedDist - projectedBox1 - projectexBox2
// 
// 
// 






class BoxCollider : public Collider
{
public:
	BoxCollider(Transform* transform, Transform offsetTransform, BoundingBox box) : Collider(transform, offsetTransform) { _boxShape = box; };
	BoxCollider(Transform* transform, Transform offsetTransform) : Collider(transform, offsetTransform) { };
	BoxCollider(BoundingBox box) : Collider() { _boxShape = box; };

	void GenerateBoundingBox(Vector3 origin, float width, float length, float height);

	virtual bool CollidesWith(Collider& other) { return other.CollidesWith(*this); };
	virtual bool CollidesWith(SphereCollider& other);
	virtual bool CollidesWith(BoxCollider& other);
	
	BoundingBox GetBox() { return _rotatedBox; }
	void RotateBox(Quaternion rotation);


private:
	bool CollidesOnAxis(BoundingBox boxA, BoundingBox boxB, Vector3 axis);
	void GetMinMax(float& min, float& max, BoundingBox box, Vector3 axis);

	BoundingBox _boxShape;
	BoundingBox _rotatedBox;

};


#endif