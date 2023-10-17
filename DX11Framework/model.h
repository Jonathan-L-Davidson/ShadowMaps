#pragma once

#ifndef MODEL_H
#define MODEL_H
#include "ModelHelpers.h"

class Shader;
class ShaderManager;

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
	XMFLOAT4 GetColor() { return _color; };

	Shader* GetShader() { return _shader; };
	void SetShader(Shader* shader) { _shader = shader; };

	void SetShaderManager(ShaderManager* manager) { _shaderManager = manager; };
	void SetupInput(ID3D11DeviceContext* context);
	void Render(ID3D11DeviceContext* context);

private:
	XMFLOAT4X4 _transform;
	XMFLOAT4 _color;

	ModelBuffer* _modelBuffer;

	Shader* _shader;
	ShaderManager* _shaderManager;
};

#endif
