#pragma once

#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#define DELETED3D(x)	if(x)	x->Release(); 

using namespace DirectX;

struct SimpleVertex
{
	XMFLOAT3 Position;
	XMFLOAT4 Color;
};

struct Shader {
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
};

struct ConstantBuffer
{
	XMMATRIX Projection;
	XMMATRIX View;
	XMMATRIX World;
};

struct Rect{
	int x;
	int y;
};
#endif