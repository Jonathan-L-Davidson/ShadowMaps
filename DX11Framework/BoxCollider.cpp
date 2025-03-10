#include "BoxCollider.h"
#include "SphereCollider.h"

using namespace DirectX; 

void BoxCollider::GenerateBoundingBox(Vector3 origin, float width, float length, float height) {
	BoundingBox box;

	// God this is suffering...
#ifndef USE_DIRECTXTK_MATH
	box.origin = origin;
	// right hand side
	box.points[0] = Vector3((width * 0.5f), (length * 0.5f), (height * 0.5f));
	box.points[1] = Vector3((width * 0.5f), -(length * 0.5f), (height * 0.5f));
	box.points[2] = Vector3((width * 0.5f), (length * 0.5f), -(height * 0.5f));
	box.points[3] = Vector3((width * 0.5f), -(length * 0.5f), -(height * 0.5f));
	// left hand side
	box.points[4] = Vector3(-(width * 0.5f), (length * 0.5f), (height * 0.5f));
	box.points[5] = Vector3(-(width * 0.5f), -(length * 0.5f), (height * 0.5f));
	box.points[6] = Vector3(-(width * 0.5f), (length * 0.5f), -(height * 0.5f));
	box.points[7] = Vector3(-(width * 0.5f), -(length * 0.5f), -(height * 0.5f));
#else
	box.Center = origin;

	box.Extents = Vector3(width, length, height);
#endif

	_boxShape = box;
}

/// <summary>
/// Updates the _translatedBox to be in worldspace.
/// </summary>
void BoxCollider::TranslateBox() {
	Vector3 pos = _tf->GetPosition() + _offsetTransform.GetPosition();
	Quaternion rotation = _tf->GetRotation() * _offsetTransform.GetRotation();

	// Create our rotation matrix.
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixIdentity();
	
	//DirectX::XMFLOAT4 rotationValue = DirectX::XMFLOAT4(rotation.v.x, rotation.v.y, rotation.v.x, rotation.n);
	DirectX::XMFLOAT4 rotationValue = DirectX::XMFLOAT4(rotation);
	
	DirectX::XMVECTOR rotationVector = DirectX::XMLoadFloat4(&rotationValue);
	rotationMatrix = DirectX::XMMatrixRotationQuaternion(rotationVector);

	_translatedBox.Center = Vector3(_boxShape.Center) + pos;
	
	// OLD WAY
	//_translatedBox.origin = _boxShape.origin + pos;

	//for (int i = 0; i < 8; i++) {
	//	// Load our position into a vector.
	//	DirectX::XMFLOAT3 posFloat = DirectX::XMFLOAT3(_boxShape.points[i].x, _boxShape.points[i].y, _boxShape.points[i].z);
	//	DirectX::XMVECTOR posV = DirectX::XMLoadFloat3(&posFloat);
	//	DirectX::XMVECTOR posTranslated = DirectX::XMVector3Transform(posV, rotationMatrix); // apply the rotation.

	//	DirectX::XMStoreFloat3(&posFloat, posTranslated); // store it back into the float.
	//	_translatedBox.points[i] = Vector3(posFloat) + pos; // add the position of the object to the newly rotated position of the box.
	//}
}

Vector3 BoxCollider::CollidesWith(SphereCollider& other) {
	BoundingBox translatedBox = GetBox(); // GetBox() updates translated box, this is the equivalent of updating our world matrix per object.
#ifdef USE_DIRECTXTK_MATH
	BoundingSphere sphere;
	sphere.Center = other.GetPosition();
	sphere.Radius = other.GetRadius();

	if (translatedBox.Intersects(sphere)) {
		Vector3 collisionHitDir = sphere.Center - translatedBox.Center;
		collisionHitDir.Normalize();
		return collisionHitDir;
	}
#else
	return CollidesOnAxis(translatedBox, other.GetPosition(), other.GetRadius());
#endif

	return Vector3::Zero;
}



/// <summary>
/// Does a basic 
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
Vector3 BoxCollider::CollidesWith(BoxCollider& other) {

#ifdef USE_DIRECTXTK_MATH
	BoundingBox boxA = GetBox();
	BoundingBox boxB = other.GetBox();

	if (boxA.Intersects(boxB)) {
		Vector3 collisionHitDir = boxB.Center - boxA.Center;
		collisionHitDir.Normalize();
		return collisionHitDir;
	}
#else
	// The axes we want to check
	Vector3 xCheck = Vector3(1, 0, 0);
	Vector3 yCheck = Vector3(0, 1, 0);
	Vector3 zCheck = Vector3(0, 0, 1);

	BoundingBox translatedBox = GetBox(); // GetBox() updates translated box, this is the equivalent of updating our world matrix per object.
	BoundingBox otherBox = other.GetBox();
	

	Vector3 xCollision = CollidesOnAxis(translatedBox, otherBox, xCheck);
	Vector3 yCollision = CollidesOnAxis(translatedBox, otherBox, yCheck);
	Vector3 zCollision = CollidesOnAxis(translatedBox, otherBox, zCheck);

	// We've collided in every axes. Therefore there is contact.
	if (!xCollision.IsZero() && !yCollision.IsZero() && !zCollision.IsZero()) {
		
		Vector3 hitDir = xCollision + yCollision + zCollision;
		float magnitude = hitDir.SquareMagnitude();
		hitDir.Normalise();
		return hitDir * magnitude;

	}
#endif // USE_DIRECTXTK_MATH
	return Vector3();
}

#ifndef USE_DIRECTXTK_MATH
Vector3 BoxCollider::CollidesOnAxis(BoundingBox boxA, Vector3 spherePos, float sphereRadius) {

	Vector3 boxToCircle = spherePos - boxA.origin;
	// Normalised axis
	Vector3 boxToCircleN = Vector3(boxToCircle);
	boxToCircleN.Normalize(); // Our axis to test for alignment, basically the closest point to the circle.

	Vector3 point = boxA.points[0];
	float furthestPoint = boxToCircleN.Dot(boxA.points[0] - boxA.origin);
	for (int i = 1; i < 8; i++) {
		Vector3 pointToTest = boxA.points[i] - boxA.origin;

		float dotTest = pointToTest.Dot(boxToCircleN);

		// Is the dot product greater than our highest? If so, replace it.
		if (dotTest > furthestPoint) {
			furthestPoint = dotTest;
			point = boxA.points[i];
		}
	}

	// If the distance between the furthest point and sphere radius is greater than the distance from the box to the circle, then it would go into the negative.
	// if the overall distance is positive, then there's a gap and there is no collision. If it's in the negative, there is collision.
	if (boxToCircle.Length() - furthestPoint - (sphereRadius * 0.5) > 0) {
		return Vector3();
	}

	Vector3 hitDir = spherePos - point;
	return hitDir;
}

Vector3 BoxCollider::CollidesOnAxis(BoundingBox boxA, BoundingBox boxB, Vector3 axis) {

	// Point A & B's min-max, this is to get a point most aligned projected onto the axis.
	float minPointA = float();
	float maxPointA = float();
	float minPointB = float();
	float maxPointB = float();

	// These functions set the minmax values for the boxes needed.
	Vector3 pointA = GetMinMax(minPointA, maxPointA, boxA, axis);
	Vector3 pointB = GetMinMax(minPointB, maxPointB, boxB, axis);

	// if the closest point of box B is greater than the furthest point of box A. OR
	// if the closest point of box A is greater than the furthest point of box B
	// there is no collision, as they aren't inside eachother. This is a standard AABB test but using the dot products instead, which "aligns" them on the axes.
	if ((minPointB > maxPointA || minPointA > maxPointB)) {
		return Vector3();
	}

	// If the conditions aren't met above, then we can assume there is collision.
	Vector3 hitDir = boxB.origin - pointA;
	return hitDir;
}

Vector3 BoxCollider::GetMinMax(float& min, float& max, BoundingBox box, Vector3 axis) {
	Vector3 minV = box.points[0];
	Vector3 maxV = box.points[0];

	// saves having to constantly generate a dot product for every vertex.
	float currentDotMin = minV.Dot(axis);
	float currentDotMax = maxV.Dot(axis);

	// For every vertice (ignoring 0 as we already generated those)
	for (int i = 1; i < 8; i++) {
		// Project the vertice to the axis.
		float testDot = box.points[i].Dot(axis);

		// if it's greater than the minimum dot product (the dot which is the least aligned)
		if (currentDotMin > testDot) {
			currentDotMin = testDot;
			minV = box.points[i];
		}

		// if it's greater than the max dot product (the dot which is most aligned)
		if (testDot > currentDotMax) {
			currentDotMax = testDot;
			maxV = box.points[i];
		}
	}
	
	// I don't like to overwrite the min and max during the for loop.
	// I'd rather do it at the end when the for loop is finished.
	min = currentDotMin;
	max = currentDotMax;
	return maxV;
}
#endif