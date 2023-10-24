#pragma once

#ifndef MODELMANAGER_H
#define MODELMANAGER_H
#include "model.h"
#include <map>
#include <string>

class Renderer;
class ShaderManager;
class TextureManager;
class Texture;

class ModelManager
{
public:
	ModelManager();
	~ModelManager();
	void Initialise();

	void AddModel(Model* model, std::string name);
	void RemoveModel(std::string name);
	Model* GetModel(std::string name);

	Texture* GetTexture(std::string path);


	std::map<std::string, Model*>* GetModels() { return _models; };

	void SetRenderManager(Renderer* renderer) { _renderManager = renderer; };

	void LoadModelFromFile(std::string path, std::string modelName);

private:
	std::map<std::string, Model*>* _models;

	Renderer* _renderManager;
	ShaderManager* _shaderManager;
	TextureManager* _textureManager;

	void CreateCube();
	void CreatePyramid();
	void CreatePlane();
};

#endif
