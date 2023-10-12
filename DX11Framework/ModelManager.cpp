#include "ModelManager.h"
#include "Renderer.h"
#include "Structures.h"
#include <fstream>
#include <sstream>
#include <random>

ModelManager::ModelManager() {
	_models = new std::map<std::string, Model*>();
};

ModelManager::~ModelManager() {
	delete _models;
}

void ModelManager::Initialise() {
    CreateCube();
    //CreatePyramid();

    LoadModelFromFile("monkey.obj", "Test Pyramid");
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
    std::default_random_engine gen;
    std::uniform_real_distribution<float> distribution(0.0, 1.0);

    int vertPos;
    // The spaghetti!! Plan on redoing this later, I can't remember how to read files.
    while (getline(modelFile, line)) {
        std::istringstream stringStream(line);

        std::string type{}, x{}, y{}, z{};

        stringStream >> type >> x >> y >> z;
        if (type == "v") {
            SimpleVertex simpleVert{
                XMFLOAT3(std::strtof(x.c_str(), NULL), std::strtof(y.c_str(), NULL), std::strtof(z.c_str(), NULL)),
                XMFLOAT4(distribution(gen), distribution(gen), distribution(gen), 0.00f)
            };
            Vertexes.push_back(simpleVert);

        }
        else if(type == "f") {

            // scuffed but it'll work?? Only works on blender based exports. Tris only, no quads!
            char splitter = '/';
            std::string temp = "", original = x;
            for (int i = 0; i < 3; i++) {
                switch (i) {
                    case(0):
                        original = x;
                        break;
                    case(1):
                        original = y;
                        break;
                    case(2):
                        original = z;
                        break;
                }
                std::istringstream iss(original);
                int state = 0;
                while (std::getline(iss, temp, splitter)) {
                    if (state == 0) {
                        Indices.push_back(std::stoi(temp.c_str()) - 1);
                    }
                    //if(state == 1) {
                    //  textures.push_back(std::stoi(temp.c_str()));
                    //}
                    
                    //if(state == 2) {
                    //  normals.push_back(std::stoi(temp.c_str()));
                    //}
                    
                    state++;
                    if (state > 2) {
                        state = 0;
                    }
                }
            }


            //WORD indice1 = std::stoi(x.c_str());
            //WORD indice2 = std::stoi(y.c_str());
            //WORD indice3 = std::stoi(z.c_str());

            //Indices.push_back(indice1);
            //Indices.push_back(indice2);
            //Indices.push_back(indice3);

        }
    }

    Model* model = new Model(_renderManager->GetDevice(), Vertexes, Indices);

    // TODO: Shader management too.
    Shader shaders = _renderManager->GetShaders();
    model->SetVertexShader(shaders.vertexShader);
    model->SetPixelShader(shaders.pixelShader);

    AddModel(model, modelName);

}