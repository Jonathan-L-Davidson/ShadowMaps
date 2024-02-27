#include "BoxCollider.h"

void BoxCollider::GenerateBoundingBox(Vector3 origin, float width, float length, float height) {
	BoundingBox box;

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

	_boxShape = box;
}

void BoxCollider::TranslateBox() {
	Vector3 pos = _tf->GetPosition() + _offsetTransform.GetPosition();
	Quaternion rotation = _tf->GetRotation() * _offsetTransform.GetRotation();

	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixIdentity();
	DirectX::XMFLOAT4 rotationValue = DirectX::XMFLOAT4(rotation.v.x, rotation.v.y, rotation.v.x, rotation.n);
	DirectX::XMVECTOR rotationVector = DirectX::XMLoadFloat4(&rotationValue);
	rotationMatrix = DirectX::XMMatrixRotationQuaternion(rotationVector);

	for (int i = 0; i < 8; i++) {
		DirectX::XMFLOAT3 posFloat = DirectX::XMFLOAT3(_boxShape.points[i].x, _boxShape.points[i].y, _boxShape.points[i].z);
		DirectX::XMVECTOR posV = DirectX::XMLoadFloat3(&posFloat);
		DirectX::XMVECTOR posTranslated = DirectX::XMVector3Transform(posV, rotationMatrix);

		DirectX::XMStoreFloat3(&posFloat, posTranslated);
		_translatedBox.points[i] = Vector3(posFloat) + pos;
	}
}

bool BoxCollider::CollidesWith(SphereCollider& other) {
	return false;
}

bool BoxCollider::CollidesWith(BoxCollider& other) {

	Vector3 xCheck = Vector3(1, 0, 0);
	Vector3 yCheck = Vector3(0, 1, 0);
	Vector3 zCheck = Vector3(0, 0, 1);

	BoundingBox otherBox = other.GetBox();
	

	bool xCollision = CollidesOnAxis(GetBox(), otherBox, xCheck);
	bool yCollision = CollidesOnAxis(GetBox(), otherBox, yCheck);
	bool zCollision = CollidesOnAxis(GetBox(), otherBox, zCheck);

	// We've collided in all axis. Therefore there is contact.
	if (xCollision && yCollision && zCollision) {
		//calculate momentum here?
		return true;
	}

	return false;
}

bool BoxCollider::CollidesOnAxis(BoundingBox boxA, BoundingBox boxB, Vector3 axis) {

	float minPointA = float();
	float maxPointA = float();
	float minPointB = float();
	float maxPointB = float();

	GetMinMax(minPointA, maxPointA, boxA, axis);
	GetMinMax(minPointB, maxPointB, boxB, axis);

	// If there is a gap between the most aligned point on this axis, then there is no collision
	if ((minPointB > maxPointA || minPointA > maxPointB)) {
		return false;
	}

	// collision!
	return true;
}

void BoxCollider::GetMinMax(float& min, float& max, BoundingBox box, Vector3 axis) {
	Vector3 minV = box.points[0];
	Vector3 maxV = box.points[0];
	float currentDotMin = minV.DotProduct(axis);
	float currentDotMax = maxV.DotProduct(axis);

	for (int i = 1; i < 8; i++) {
		float testDot = box.points[i].DotProduct(axis);

		if (currentDotMin > testDot) {
			currentDotMin = testDot;
			minV = box.points[i];
		}

		if (testDot > currentDotMax) {
			currentDotMax = testDot;
			maxV = box.points[i];
		}
	}

	min = currentDotMin;
	max = currentDotMax;
}