#include "TextureManager.h"
#include "DDSTextureLoader.h"
#include <stdexcept>

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
	std::string fullPath = "Textures\\" + path + ".dds";
	std::wstring widePath = std::wstring(fullPath.begin(), fullPath.end());

	// Texture construction.
	Texture* tex = new Texture();
	ID3D11ShaderResourceView* texturePath = tex->GetResourceTexture();
	
	// Load the texture file.
	HRESULT hr = S_OK;
	hr = CreateDDSTextureFromFile(_device, widePath.c_str(), nullptr, &texturePath);
	
	if(FAILED(hr)) {
		throw std::invalid_argument("Texture failed to be created");
		delete tex;
		return;
	}

	tex->SetSampler(_bilinearSamplerState);
	tex->SetID(path);
	tex->SetResourceTexture(texturePath);
	// Add it to the texture list.
	_textures->insert(std::make_pair(path, tex));

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
	bilinearSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	bilinearSamplerDesc.MaxLOD = 1;
	bilinearSamplerDesc.MinLOD = 0;

	hr = _device->CreateSamplerState(&bilinearSamplerDesc, &_bilinearSamplerState);
	if (FAILED(hr)) {
		throw std::invalid_argument("Sampler failed to initialise.");
		return;
	}
	
}

void TextureManager::RemoveTexture(std::string path) {
	_textures->erase(path);
}