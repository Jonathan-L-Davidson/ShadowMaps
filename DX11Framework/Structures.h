#pragma once

#if !defined(STRUCTURES_H)
#define STRUCTURES_H
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

using namespace DirectX;

struct SimpleVertex
{
	XMFLOAT3 Position;
	XMFLOAT4 Color;
};

struct ConstantBuffer
{
	XMMATRIX Projection;
	XMMATRIX View;
	XMMATRIX World;
};

#endif