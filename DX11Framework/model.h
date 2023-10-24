#pragma once

#ifndef MODEL_H
#define MODEL_H
#include "ModelHelpers.h"
#include <string>

class Shader;
class ShaderManager;
class Buffer;
class Texture;

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

	Shader* GetShader() { return _shader; };
	void SetShader(Shader* shader) { _shader = shader; };
	void SetShader(std::string shaderFile);

	ShaderManager* GetShaderManager() { return _shaderManager; };
	void SetShaderManager(ShaderManager* manager) { _shaderManager = manager; };
	void SetupInput(ID3D11DeviceContext* context);
	void SetupTextures(ID3D11DeviceContext* context);
	void Render(ID3D11DeviceContext* context);
	void UpdateCBData(ConstantBuffer* cbData);

	Texture* GetTexture() { return _texture; }
	void SetTexture(Texture* texture) { _texture = texture; }

private:
	XMFLOAT4X4 _transform;

	ModelBuffer* _modelBuffer;
	XMFLOAT4 _diffuseLight = XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f);
	XMFLOAT4 _diffuseMaterial = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SimpleLight _light;

	XMFLOAT4 _specularLight = XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f);
	XMFLOAT4 _specularMaterial = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	float _specPower = 10.0f;


	Shader* _shader;
	ShaderManager* _shaderManager;

	Texture* _texture;
};

#endif
