#pragma once

#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "GlobalDefines.h"

#define DELETED3D(x)	if(x)	x->Release(); 

using namespace DirectX;

enum LightType {
	DISABLED = 0,
	POINT_LIGHT,
	SPOT_LIGHT,
	DIRECTIONAL_LIGHT,
};

struct SimpleLight {
	// 16 bytes
	XMFLOAT4 Position;
	//
	
	// 16 bytes
	XMFLOAT3 Rotation;
	int Type = LightType::DISABLED; 

	// 16 bytes
	XMFLOAT3 DiffuseColor; // Diffuse lighting color from light.
	float ConeCoef;

	// 16 bytes
	XMFLOAT3 SpecColor; // Specular shining color from light.
	float SpecPower;

	XMMATRIX view;
	XMMATRIX projection; 

	// Todo: Change this to calculate the inverse square law instead. This works for now however.
	// 16 bytes
	float FalloffDistance; // How far the gradient will be.
	float FalloffDropDistance; // I dont actually know what to call this, this is the distance before falling off.
	float FalloffGradientCoefficiency; // How quick the gradient takes to fade.
	int padding2;
	//


};

struct SimpleVertex
{
	XMFLOAT3 Position;
	XMFLOAT3 Normal;
	XMFLOAT2 TexCoord;
};

struct ConstantBuffer
{
	XMMATRIX Projection;
	XMMATRIX View;
	XMMATRIX World;

	XMFLOAT4 AmbientLight;
	XMFLOAT4 DiffuseMaterial;
	XMFLOAT4 SpecularMaterial;

	SimpleLight Lights[MAX_LIGHTS];
	
	XMFLOAT3 CameraPos;
	unsigned int UseTexture;

	unsigned int UseDiffuse;
	unsigned int UseDisplacement;
	unsigned int UseNormal;
	unsigned int UseSpecular;

};

struct Rect{
	int x;
	int y;
};

#endif