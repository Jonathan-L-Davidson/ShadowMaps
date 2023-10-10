#pragma once

#ifndef MODEL_H
#define MODEL_H
#include "ModelHelpers.h"

class Model
{
public:
	Model(ID3D11Device* device);
	Model(ID3D11Device* device, std::vector<SimpleVertex> verts, std::vector<WORD> indices);
	~Model();
	int GetIndices() { return _modelBuffer->GetIndBuffer()->GetCount(); };
	ModelBuffer* GetModelBuffer() { return _modelBuffer; };
	void SetTransform(XMFLOAT4X4 transform) { _transform = transform; };
	XMFLOAT4X4 GetTransform() { return _transform; };

	void SetVertexShader(ID3D11VertexShader* shader) { _vertexShader = shader; };
	void SetPixelShader(ID3D11PixelShader* shader) { _pixelShader = shader; };

	void Render(ID3D11DeviceContext* context);

private:
	XMFLOAT4X4 _transform;

	ModelBuffer* _modelBuffer;

	ID3D11VertexShader* _vertexShader;
	ID3D11PixelShader* _pixelShader;
	
};

#endif
