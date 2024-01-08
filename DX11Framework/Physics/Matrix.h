#pragma once
#include "Core.h"
#include <DirectXMath.h>
#include "Vector3.h"
// This translates the Vector3 system into a usable XMMatrix. It is coupled unfortunately.


namespace Physics {

	Vector3 GetTranslationFromMatrix(const DirectX::XMFLOAT4X4 matrix) {
		
		DirectX::XMVECTOR translationRaw;
		DirectX::XMVECTOR scaleRaw;
		DirectX::XMVECTOR rotationRaw;

		DirectX::XMMatrixDecompose(&scaleRaw, &rotationRaw, &translationRaw, DirectX::XMLoadFloat4x4(&matrix));

		DirectX::XMFLOAT3 translation;
		DirectX::XMStoreFloat3(&translation, translationRaw);

		return Vector3(translation.x, translation.y, translation.z);
	}

	DirectX::XMMATRIX MatrixFromTransform(Vector3 pos, Vector3 rot, Vector3 scale) {
		DirectX::XMMATRIX matrix = DirectX::XMMatrixIdentity();


		matrix *= DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
		matrix *= DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
		matrix *= DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);

		return matrix;
	}
	
}