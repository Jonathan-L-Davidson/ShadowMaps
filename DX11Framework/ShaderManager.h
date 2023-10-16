#pragma once

#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include <d3d11_4.h>
#include <string>
#include <map>

class Shader {
public:
	Shader();
	~Shader();

	ID3D11VertexShader* GetVertexShader();
	ID3D11PixelShader* GetPixelShader();
	void SetVertexShader(ID3D11VertexShader* vertShader) { _vertexShader = vertShader; };
	void SetPixelShader(ID3D11PixelShader* pixelShader) { _pixelShader = pixelShader; };


	std::string GetID() { return _id; };
	void SetID(std::string id) { _id = id};
	void SetDefault(Shader* shader) { _default = shader; };

private:
	ID3D11VertexShader* _vertexShader;
	ID3D11PixelShader* _pixelShader;

	std::string _id;
	Shader* _default; // default callback if anything goes wrong.
};

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();
	void Initialise();

	Shader* GetDefaultShader() { return GetShader("Default"); };
	Shader* GetShader() { return GetDefaultShader(); };
	Shader* GetShader(std::string id);

	void AddShader(Shader* shader, std::string id);
	void AddShader(std::string id);

	void RemoveShader(std::string id);

	void SetDevice(ID3D11Device* device) { _device = device; };
private:
	std::map<std::string, Shader*>* _shaders;

	ID3D11InputLayout* _inputLayout;
	ID3D11Device* _device;

	void CreateShaderFromFile(std::string);
	void CreateDefaultShader();
};

#endif
