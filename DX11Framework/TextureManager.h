#pragma once

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "structures.h"
#include "string"
#include <map>

enum TextureType {
	DIFFUSE = 0,
	SPECULAR,
	DISPLACEMENT,
	NORMAL,
};

class Texture
{
public:
	std::string GetID() { return _id; };
	void SetID(std::string id) { _id = id; };

	ID3D11ShaderResourceView* GetResourceTexture(TextureType type) { 
		switch (type) {
		case(DIFFUSE):
			return _diffuseTexture;
			break;
		case(SPECULAR):
			return _specularTexture;
			break;
		case(DISPLACEMENT):
			return _displacementTexture;
			break;
		case(NORMAL):
			return _normalTexture;
			break;
		}
	}
	void SetResourceTexture(ID3D11ShaderResourceView* texture, TextureType type) {
		switch (type) {
			case(DIFFUSE):
				_diffuseTexture = texture;
				hasDiffuse = true;
				break;
			case(SPECULAR):
				_specularTexture = texture;
				hasSpecular = true;
				break;
			case(DISPLACEMENT):
				_displacementTexture = texture;
				hasDisplacement = true;
				break;
			case(NORMAL):
				_normalTexture = texture;
				hasNormal = true;
				break;
		}
	}

	ID3D11SamplerState* GetSampler() { return _sampler; }
	void SetSampler(ID3D11SamplerState* sampler) { _sampler = sampler; }

	bool hasDiffuse = false;
	bool hasSpecular = false;
	bool hasDisplacement = false;
	bool hasNormal = false;

private:
	std::string _id;

	ID3D11ShaderResourceView* _diffuseTexture;
	ID3D11ShaderResourceView* _displacementTexture;
	ID3D11ShaderResourceView* _specularTexture;
	ID3D11ShaderResourceView* _normalTexture;
	ID3D11SamplerState* _sampler;
};

class TextureManager
{
public:

	TextureManager();
	~TextureManager();
	void Initialise();

	void CreateDefaultTexture();
	Texture* GetDefaultTexture();

	void AddTexture(Texture* texture, std::string path);
	void AddTexture(std::string path);
	Texture* LoadTextureFromFile(std::string, TextureType type);
	Texture* GetTexture(std::string path);
	
	void CreateSampler();
	ID3D11SamplerState* GetSampler() { return _bilinearSamplerState; }

	void RemoveTexture(std::string path);

	void SetDevice(ID3D11Device* device) { _device = device; };

private:
	std::map<std::string, Texture*>* _textures;

	ID3D11Device* _device;
	ID3D11SamplerState* _bilinearSamplerState;
};

#endif // !TEXTUREMANAGER_H
