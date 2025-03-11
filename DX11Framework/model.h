#pragma once

#ifndef MODEL_H
#define MODEL_H
#include "ModelHelpers.h"
#include <string>

#include "DirectXMesh.h"
#include "WaveFrontReader.h"

class Shader;
class ShaderManager;
class Buffer;
class Texture;
class Transform;

class Model
{
public:
	Model(ID3D11Device* device);
	Model(ID3D11Device* device, std::list<SimpleVertex> verts, std::list<DWORD> indices);
	~Model();
	int GetIndices() { return _modelBuffer->GetIndBuffer()->GetCount(); };
	ModelBuffer* GetModelBuffer() { return _modelBuffer; };
	
	Shader* GetShader() { return _shader; };
	void SetShader(Shader* shader) { _shader = shader; };
	void SetShader(std::string shaderFile);

	ShaderManager* GetShaderManager() { return _shaderManager; };
	void SetShaderManager(ShaderManager* manager) { _shaderManager = manager; };
	void SetupInput(ID3D11DeviceContext* context);
	void SetupTextures(ID3D11DeviceContext* context);
	void Render(ID3D11DeviceContext* context, bool ignoreShader = 0);
	void UpdateCBData(ConstantBuffer* cbData);

	Texture* GetTexture() { return _texture; }
	void SetTexture(Texture* texture) { _texture = texture; }

	Transform* transform;
private:

	ModelBuffer* _modelBuffer;
	XMFLOAT4 _diffuseMaterial = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	XMFLOAT4 _specularMaterial = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	unsigned int _useTexture = 0;

	Shader* _shader;
	ShaderManager* _shaderManager;

	Texture* _texture;
};

#endif
