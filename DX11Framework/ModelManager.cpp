#include "ModelManager.h"
#include "Renderer.h"
#include "Structures.h"
#include <fstream>
#include <sstream>

ModelManager::ModelManager() {
	_models = new std::map<std::string, Model*>();
};

ModelManager::~ModelManager() {
	delete _models;
}

void ModelManager::Initialise() {
    CreateCube();
    //CreatePyramid();

    LoadModelFromFile("space_station.obj", "Test Pyramid");
}

void ModelManager::AddModel(Model* model, std::string name) {
	_models->insert(std::make_pair(name, model));
}

void ModelManager::RemoveModel(std::string name) {
	_models->erase(name);
}

Model* ModelManager::GetModel(std::string name) {
	Model* model = _models->find(name)->second;
	return model;
}

void ModelManager::CreateCube() {
    std::vector<SimpleVertex> VertexData = {
        //Position                     //Color             
        { XMFLOAT3(-1.00f,  1.00f, -1.00f), XMFLOAT4(1.0f,  0.0f, 0.0f,  0.0f)},
        { XMFLOAT3(1.00f,  1.00f, -1.00f),  XMFLOAT4(0.0f,  1.0f, 0.0f,  0.0f)},
        { XMFLOAT3(-1.00f, -1.00f, -1.00f), XMFLOAT4(0.0f,  0.0f, 1.0f,  0.0f)},
        { XMFLOAT3(1.00f, -1.00f, -1.00f),  XMFLOAT4(1.0f,  0.6f, 0.4f,  0.0f)},
        { XMFLOAT3(-1.00f,  1.00f, 1.00f), XMFLOAT4(1.0f,  1.0f, 0.0f,  0.0f)},
        { XMFLOAT3(1.00f,  1.00f, 1.00f),  XMFLOAT4(0.0f,  1.0f, 1.0f,  0.0f)},
        { XMFLOAT3(-1.00f, -1.00f, 1.00f), XMFLOAT4(1.0f,  0.0f, 1.0f,  0.0f)},
        { XMFLOAT3(1.00f, -1.00f, 1.00f),  XMFLOAT4(0.5f,  0.5f, 1.0f,  0.0f)},
    };

    std::vector<WORD> IndexData = {
        //Indices
        0,1,2,
        2,1,3,
        5,7,3,
        5,3,1,
        7,5,4,
        6,7,4,
        6,4,0,
        0,2,6,
        5,1,4,
        4,1,0,
        3,7,6,
        3,6,2,
    };

    Model* model = new Model(_renderManager->GetDevice(), VertexData, IndexData);

    // TODO: Shader management too.
    Shader shaders = _renderManager->GetShaders();
    model->SetVertexShader(shaders.vertexShader);
    model->SetPixelShader(shaders.pixelShader);

    AddModel(model, "Test Cube");
}

void ModelManager::CreatePyramid() {
    std::vector<SimpleVertex> VertexData = {
        //Position                     //Color             
        { XMFLOAT3(0.00f,  1.00f, 0.00f), XMFLOAT4(1.0f,  0.0f, 0.0f,  0.0f)},
        { XMFLOAT3(-1.00f, -1.00f, -1.00f), XMFLOAT4(0.0f,  0.0f, 1.0f,  0.0f)},
        { XMFLOAT3(1.00f, -1.00f, -1.00f),  XMFLOAT4(1.0f,  0.6f, 0.4f,  0.0f)},
        { XMFLOAT3(-1.00f, -1.00f, 1.00f), XMFLOAT4(1.0f,  0.0f, 1.0f,  0.0f)},
        { XMFLOAT3(1.00f, -1.00f, 1.00f),  XMFLOAT4(0.5f,  0.5f, 1.0f,  0.0f)},
    };

    std::vector<WORD> IndexData = {
        //Indices
        2,1,0,
        2,0,4,
        4,0,3,
        0,1,3,
        2,4,3,
        1,2,3,
    };

    Model* model = new Model(_renderManager->GetDevice(), VertexData, IndexData);
    
    // TODO: Shader management too.
    Shader shaders = _renderManager->GetShaders();
    model->SetVertexShader(shaders.vertexShader);
    model->SetPixelShader(shaders.pixelShader);
    
    AddModel(model, "Test Pyramid");
}

void ModelManager::LoadModelFromFile(std::string path, std::string modelName) {
    std::ifstream modelFile;

    modelFile.open(path);
    
    std::vector<SimpleVertex> Vertexes;
    std::vector<WORD> Indices;

    if (!modelFile) {
        // throw an error!!!
        return;
    }

    std::string line;

    int vertPos;
    // The spaghetti!! Plan on redoing this later, I can't remember how to read files.
    while (getline(modelFile, line)) {
        std::istringstream stringStream(line);

        std::string type{}, x{}, y{}, z{};

        stringStream >> type >> x >> y >> z;

        if (type == "v") {
            SimpleVertex simpleVert{
                XMFLOAT3(std::strtof(x.c_str(), NULL), std::strtof(y.c_str(), NULL), std::strtof(z.c_str(), NULL)),
                XMFLOAT4(0.8f, 0.75f, 0.60f, 0.00f)
            };
            Vertexes.push_back(simpleVert);

        }
        else if(type == "f") {

            // scuffed but it'll work?
            WORD indice1 = std::stoi(x.c_str());
            WORD indice2 = std::stoi(y.c_str());
            WORD indice3 = std::stoi(z.c_str());

            Indices.push_back(indice1);
            Indices.push_back(indice2);
            Indices.push_back(indice3);

        }
    }

    Model* model = new Model(_renderManager->GetDevice(), Vertexes, Indices);

    // TODO: Shader management too.
    Shader shaders = _renderManager->GetShaders();
    model->SetVertexShader(shaders.vertexShader);
    model->SetPixelShader(shaders.pixelShader);

    AddModel(model, modelName);

}