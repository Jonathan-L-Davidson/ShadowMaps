#pragma once

#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#define DELETED3D(x)	if(x)	x->Release(); 

using namespace DirectX;

struct SimpleLight {
	XMFLOAT4 Position;
	XMFLOAT3 Rotation;
};

struct SimpleVertex
{
	XMFLOAT3 Position;
	XMFLOAT3 Normal;
};

struct ConstantBuffer
{
	XMMATRIX Projection;
	XMMATRIX View;
	XMMATRIX World;
	XMFLOAT4 AmbientLight;
	XMFLOAT4 DiffuseLight;
	XMFLOAT4 DiffuseMaterial;

	XMFLOAT4 LightPosition;
	XMFLOAT3 LightRotation;

	XMFLOAT4 SpecularLight;
	XMFLOAT4 SpecularMaterial;
	float    SpecPower;

	XMFLOAT3 CameraPos;

	float Time;
};

struct Rect{
	int x;
	int y;
};
#endif