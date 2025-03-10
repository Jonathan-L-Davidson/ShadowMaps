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

	Texture();
	~Texture();
	
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
				hasDiffuse = 1;
				break;
			case(SPECULAR):
				_specularTexture = texture;
				hasSpecular = 1;
				break;
			case(DISPLACEMENT):
				_displacementTexture = texture;
				hasDisplacement = 1;
				break;
			case(NORMAL):
				_normalTexture = texture;
				hasNormal = 1;
				break;
		}
	}

	ID3D11SamplerState* GetSampler() { return _sampler; }
	void SetSampler(ID3D11SamplerState* sampler) { _sampler = sampler; }

	unsigned int hasDiffuse = 0;
	unsigned int hasSpecular = 0;
	unsigned int hasDisplacement = 0;
	unsigned int hasNormal = 0;

private:
	std::string _id;

	ID3D11ShaderResourceView* _diffuseTexture;
	ID3D11ShaderResourceView* _displacementTexture;
	ID3D11ShaderResourceView* _specularTexture;
	ID3D11ShaderResourceView* _normalTexture;
	ID3D11SamplerState* _sampler;
};

struct TextureList {
	std::string strName;
	std::string strTexture;
	std::string strNormalTexture;
	std::string strSpecularTexture;
	std::string strEmissiveTexture;
	std::string strRMATexture;
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
	void AddTexture(std::string path, TextureList textureList);
	void AddTexture(std::string path);
	void LoadTextureFromPath(std::string path, Texture* texture, TextureType type);
	Texture* LoadTextureFromFile(std::string path);
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
