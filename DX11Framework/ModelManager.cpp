#include "ModelManager.h"
#include "Renderer.h"
#include "Structures.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include <fstream>
#include <sstream>
#include <random>

ModelManager::ModelManager() {
	_models = new std::map<std::string, Model*>();
};

ModelManager::~ModelManager() {
    for (auto obj : *_models) {
        delete obj.second;
    }
    _models->clear();

    _renderManager = nullptr;
    delete _shaderManager;
}

void ModelManager::Initialise() {
    // Initialise the shader manager
    _shaderManager = new ShaderManager();
    _shaderManager->SetDevice(_renderManager->GetDevice());
    _shaderManager->Initialise();

    // Initialise the texture manager
    _textureManager = new TextureManager();
    _textureManager->SetDevice(_renderManager->GetDevice());
    _textureManager->Initialise();

    // Create the hardcoded models
    CreateCube();
    CreatePyramid();
    CreatePlane();

    // Load some base .obj files
    LoadModelFromFile("monkey.obj", "Monkey");
    LoadModelFromFile("cube.obj", "Cube");
}

void ModelManager::AddModel(Model* model, std::string name) {
    model->SetShaderManager(_shaderManager);
	_models->insert(std::make_pair(name, model));
}

void ModelManager::RemoveModel(std::string name) {
	_models->erase(name);
}

Model* ModelManager::GetModel(std::string name) {
	Model* model = _models->find(name)->second;
	return model;
}

Texture* ModelManager::GetTexture(std::string path) {
    return _textureManager->GetTexture(path);
}

Shader* ModelManager::GetShader(std::string path) {
    return _shaderManager->GetShader(path);
}

void ModelManager::CreateCube() {
    std::list<SimpleVertex> VertexData = {
        //Position                          //Normal                            // TexCoords
        { XMFLOAT3(-1.00f,  1.00f, -1.00f), XMFLOAT3(-1.00f,  1.00f, -1.00f),   XMFLOAT2(0.0f, 0.0f)}, // 0
        { XMFLOAT3(1.00f,  1.00f, -1.00f),  XMFLOAT3(1.00f,  1.00f, -1.00f),    XMFLOAT2(1.0f, 0.0f)}, // 1
        { XMFLOAT3(-1.00f, -1.00f, -1.00f), XMFLOAT3(-1.00f, -1.00f, -1.00f),   XMFLOAT2(0.0f, 1.0f)}, // 2
        { XMFLOAT3(1.00f, -1.00f, -1.00f),  XMFLOAT3(1.00f, -1.00f, -1.00f),    XMFLOAT2(1.0f, 1.0f)}, // 3
        { XMFLOAT3(-1.00f,  1.00f, 1.00f),  XMFLOAT3(-1.00f,  1.00f, 1.00f),    XMFLOAT2(1.0f, 0.0f)}, // 4
        { XMFLOAT3(1.00f,  1.00f, 1.00f),   XMFLOAT3(1.00f,  1.00f, 1.00f),     XMFLOAT2(0.0f, 0.0f)}, // 5
        { XMFLOAT3(-1.00f, -1.00f, 1.00f),  XMFLOAT3(-1.00f, -1.00f, 1.00f),    XMFLOAT2(1.0f, 1.0f)}, // 6
        { XMFLOAT3(1.00f, -1.00f, 1.00f),   XMFLOAT3(1.00f, -1.00f, 1.00f),     XMFLOAT2(0.0f, 1.0f)}, // 7
    };

    std::list<DWORD> IndexData = {
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

    model->SetShader(_shaderManager->GetDefaultShader());

    AddModel(model, "Test Cube");
}

void ModelManager::CreatePyramid() {
    std::list<SimpleVertex> VertexData = {
        //Position                          //Normal                            // TexCoords
        { XMFLOAT3(0.00f,  1.00f, 0.00f),   XMFLOAT3(0.00f,  1.00f, 0.00f),     XMFLOAT2(0.5f, 0.5f)},
        { XMFLOAT3(-1.00f, -1.00f, -1.00f), XMFLOAT3(-1.00f, -1.00f, -1.00f),   XMFLOAT2(0.0f, 0.0f)},
        { XMFLOAT3(1.00f, -1.00f, -1.00f),  XMFLOAT3(1.00f, -1.00f, -1.00f),    XMFLOAT2(1.0f, 0.0f)},
        { XMFLOAT3(-1.00f, -1.00f, 1.00f),  XMFLOAT3(-1.00f, -1.00f, 1.00f),    XMFLOAT2(0.0f, 1.0f)},
        { XMFLOAT3(1.00f, -1.00f, 1.00f),   XMFLOAT3(1.00f, -1.00f, 1.00f),     XMFLOAT2(1.0f, 1.0f)},
    };                                                                          

    std::list<DWORD> IndexData = {
        //Indices
        2,1,0,
        2,0,4,
        4,0,3,
        0,1,3,
        2,4,3,
        1,2,3,
    };

    Model* model = new Model(_renderManager->GetDevice(), VertexData, IndexData);
    
    model->SetShader(_shaderManager->GetDefaultShader());

    AddModel(model, "Test Pyramid");
}

void ModelManager::CreatePlane() {
    std::list<SimpleVertex> VertexData = {
        //Position                          //Normal                         // TexCoords
        { XMFLOAT3(50.00f,  0.00f, 50.00f),  XMFLOAT3(50.00f, 0.0f, 50.00f),  XMFLOAT2(0.0f, 0.0f)},
        { XMFLOAT3(-50.00f, 0.00f, -50.00f), XMFLOAT3(-50.00f, 0.0f, -50.00f),  XMFLOAT2(1.0f, 0.0f)},
        { XMFLOAT3(50.00f,  0.00f, -50.00f), XMFLOAT3(50.00f, 0.0f, -50.00f),  XMFLOAT2(0.0f, 1.0f)},
        { XMFLOAT3(-50.00f, 0.00f, 50.00f),  XMFLOAT3(-50.00f, 0.0f, 50.00f),  XMFLOAT2(1.0f, 1.0f)},
    };

    std::list<DWORD> IndexData = {
        //Indices
        3,0,1,
        2,1,0,
    };


    Model* model = new Model(_renderManager->GetDevice(), VertexData, IndexData);

    model->SetShader(_shaderManager->GetDefaultShader());

    AddModel(model, "Floor Plane");
}

Model* ModelManager::LoadModelFromFile(std::string path, std::string modelName) {
    std::ifstream modelFile;

    std::string tempPath = "Models\\" + path;

    modelFile.open(tempPath);
    
    std::list<SimpleVertex> SimpleVerts;
    std::list<XMFLOAT3> Vertices;
    std::list<XMFLOAT3> Normals;
    std::list<XMFLOAT2> Textures;
    std::list<DWORD> Indices;

    if (!modelFile) {
        // throw an error!!!
        throw std::invalid_argument("No ModelFile!");
        return nullptr;
    }

    std::string line;
    std::default_random_engine gen;
    std::uniform_real_distribution<float> distribution(0.0, 1.0);

    int indiceCount = 0;
    // This part took a while to recreate, requiring me to understand how to make use of stringstreams instead of using a single filestream.
    while (getline(modelFile, line)) {
        std::istringstream stringStream(line);

        std::string type{}, x{}, y{}, z{}; 

        stringStream >> type >> x >> y >> z; // This splits each line into 4 elements.

        if (type[0] == 'v') { // Are we dealing with a vertex?
            
            if (type == "v") { // Vertices!
                Vertices.push_back(XMFLOAT3(std::strtof(x.c_str(), NULL), std::strtof(y.c_str(), NULL), std::strtof(z.c_str(), NULL)));
            };

            if (type == "vn") { // Normals!
                Normals.push_back(XMFLOAT3(std::strtof(x.c_str(), NULL), std::strtof(y.c_str(), NULL), std::strtof(z.c_str(), NULL)));
            }

            if (type == "vt") { // Textures!
                Textures.push_back(XMFLOAT2(std::strtof(x.c_str(), NULL), std::strtof(y.c_str(), NULL)));
            }
        }

        if(type == "f") { // Faces, the painful part!

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
                
                SimpleVertex simpleVert;

                while (std::getline(iss, temp, splitter)) {
                    if (state == 0) { // v
                        simpleVert.Position = *std::next(Vertices.begin(), std::stoi(temp.c_str()) - 1);
                    }
                    
                    if(state == 1) { // vt
                        simpleVert.TexCoord = *std::next(Textures.begin(), std::stoi(temp.c_str()) - 1);
                    }
                    
                    if(state == 2) { // vn
                        simpleVert.Normal = *std::next(Normals.begin(), std::stoi(temp.c_str()) - 1);
                    }
                    
                    state++; // Handle reading the `v/vt/vn` state swapping
                    if (state > 2) {
                        state = 0; // reset back to v
                    }
                }

                SimpleVerts.push_back(simpleVert);
                Indices.push_back(indiceCount);
                indiceCount++;
            }
        }
    }

    Model* model = new Model(_renderManager->GetDevice(), SimpleVerts, Indices);

    model->SetShader(_shaderManager->GetDefaultShader());

    AddModel(model, modelName);
    return model;
}

void ModelManager::CreateShader(std::string path) {
    _shaderManager->AddShader(path);
}