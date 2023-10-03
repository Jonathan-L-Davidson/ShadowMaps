#pragma once

#if !defined(MODEL_H)
#define MODEL_H
#include "ModelHelpers.h"

class Model
{
public:
	Model(ID3D11Device* device);
	Model(ID3D11Device* device, std::list<SimpleVertex> verts, std::list<WORD> indices);
	~Model();
	int GetIndices() { return _modelBuffer->GetIndBuffer()->GetCount(); };
	ModelBuffer* GetModelBuffer() { return _modelBuffer; };
	void SetPosition(XMFLOAT3 pos) { _position = pos; };
	void SetVertexShader(ID3D11VertexShader* shader) { _vertexShader = shader; };
	void SetPixelShader(ID3D11PixelShader* shader) { _pixelShader = shader; };

	void Render(ID3D11DeviceContext* context);

private:
	XMFLOAT3 _position;

	ModelBuffer* _modelBuffer;

	ID3D11VertexShader* _vertexShader;
	ID3D11PixelShader* _pixelShader;
	
};

#endif
