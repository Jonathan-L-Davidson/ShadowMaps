#include "TextureManager.h"
#include "DDSTextureLoader.h"
#include "FileHelpers.h"
#include <stdexcept>

Texture::Texture() {

}

Texture::~Texture() {
	DELETED3D(_diffuseTexture);
	DELETED3D(_displacementTexture);
	DELETED3D(_specularTexture);
	DELETED3D(_normalTexture);
	DELETED3D(_sampler);

}


TextureManager::TextureManager() {
	_textures = new std::map<std::string, Texture*>();
}

TextureManager::~TextureManager() {
	for (auto tex : *_textures) {
		delete tex.second;
	}
	_textures->clear();

	_device = nullptr;
	DELETED3D(_bilinearSamplerState);
}

void TextureManager::Initialise() {
	CreateSampler();
	CreateDefaultTexture();
}

void TextureManager::CreateDefaultTexture() {
	AddTexture("Default");
}

Texture* TextureManager::GetDefaultTexture() {
	return GetTexture("Default");
}

void TextureManager::AddTexture(Texture* texture, std::string path) {
	texture->SetID(path);
	_textures->insert(std::make_pair(path, texture));

}

void TextureManager::AddTexture(std::string path) {
	if (_textures->count(path)) {
		return;
	}


	// Sets the path correctly to a texture file.
	std::string diffusePath = "Textures\\" + path + "_COLOR.dds";
	std::string displacementPath = "Textures\\" + path + "_DISP.dds";
	std::string normalPath = "Textures\\" + path + "_NRM.dds";
	std::string specularPath = "Textures\\" + path + "_SPEC.dds";

	// Texture construction.
	Texture* tex = new Texture();

	if (Helpers::FileExists(diffusePath.c_str())) {
		LoadTextureFromPath(diffusePath, tex, TextureType::DIFFUSE);
	}
	if (Helpers::FileExists(displacementPath.c_str())) {
		LoadTextureFromPath(displacementPath, tex, TextureType::DISPLACEMENT);
	}
	if (Helpers::FileExists(normalPath.c_str())) {
		LoadTextureFromPath(normalPath, tex, TextureType::NORMAL);
	}
	if (Helpers::FileExists(specularPath.c_str())) {
		LoadTextureFromPath(specularPath, tex, TextureType::SPECULAR);
	}


	tex->SetSampler(_bilinearSamplerState);
	tex->SetID(path);
	// Add it to the texture list.
	_textures->insert(std::make_pair(path, tex));
}

void TextureManager::LoadTextureFromPath(std::string path, Texture* texture, TextureType type) {

	std::wstring widePath = std::wstring(path.begin(), path.end());
	
	ID3D11ShaderResourceView* texturePath;
	texturePath = texture->GetResourceTexture(type);
	
	// Load the texture file.
	HRESULT hr = S_OK;
	hr = CreateDDSTextureFromFile(_device, widePath.c_str(), nullptr, &texturePath);

	if (FAILED(hr)) {
		throw std::invalid_argument("Texture failed to be created");
		delete texture;
		return;
	}

	// Set the texture to the model and enable the correct texture type.
	texture->SetResourceTexture(texturePath, type);

	switch (type) {
	case(DIFFUSE):
		texture->hasDiffuse = 1;
		break;
	case(SPECULAR):
		texture->hasSpecular = 1;
		break;
	case(DISPLACEMENT):
		texture->hasDisplacement = 1;
		break;
	case(NORMAL):
		texture->hasNormal = 1;
		break;
	}
}

Texture* TextureManager::GetTexture(std::string path) {
	if (_textures->count(path)) {
		return _textures->find(path)->second;
	}

	AddTexture(path);
	return GetTexture(path);
}

void TextureManager::CreateSampler() {
	HRESULT hr = S_OK;

	D3D11_SAMPLER_DESC bilinearSamplerDesc = {};
	bilinearSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	bilinearSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	bilinearSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	bilinearSamplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	bilinearSamplerDesc.MaxLOD = MAXINT;
	bilinearSamplerDesc.MinLOD = 0;
	bilinearSamplerDesc.MaxAnisotropy = 16;
	bilinearSamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

	hr = _device->CreateSamplerState(&bilinearSamplerDesc, &_bilinearSamplerState);
	if (FAILED(hr)) {
		throw std::invalid_argument("Sampler failed to initialise.");
		return;
	}
	
}

void TextureManager::RemoveTexture(std::string path) {
	_textures->erase(path);
}