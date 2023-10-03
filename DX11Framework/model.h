#pragma once

#if !defined(MODEL_CLASS)
#define MODEL_CLASS

#include <DirectXMath.h>
#include "ModelHelpers.h"

class Model
{
public:
	Model(ID3D11Device* device);
	Model(ID3D11Device* device, std::list<SimpleVertex> verts, std::list<WORD> indices);
	~Model();
	int GetIndices() { return _modelBuffer->GetIndBuffer()->GetCount(); };
	void SetPosition(XMFLOAT3 pos) { _position = pos; };
	void Render(ID3D11DeviceContext* context);
	void SetVertexShader(ID3D11VertexShader* shader) { _vertexShader = shader; };
	void SetPixelShader(ID3D11PixelShader* shader) { _pixelShader = shader; };
private:
	XMFLOAT3 _position;

	ModelBuffer* _modelBuffer;

	ID3D11VertexShader* _vertexShader;
	ID3D11PixelShader* _pixelShader;
	
};

#endif