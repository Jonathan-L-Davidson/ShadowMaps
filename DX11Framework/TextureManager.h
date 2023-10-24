#pragma once

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "structures.h"
#include "string"
#include <map>

class Texture
{
public:
	std::string GetID() { return _id; };
	void SetID(std::string id) { _id = id; };

	ID3D11ShaderResourceView* GetResourceTexture() { return _texture; }
	void SetResourceTexture(ID3D11ShaderResourceView* texture) { _texture = texture; }

	ID3D11SamplerState* GetSampler() { return _sampler; }
	void SetSampler(ID3D11SamplerState* sampler) { _sampler = sampler; }

private:
	std::string _id;

	ID3D11ShaderResourceView* _texture;
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
