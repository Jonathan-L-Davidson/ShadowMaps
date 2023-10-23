#include "ModelManager.h"
#include "Renderer.h"
#include "Structures.h"
#include "ShaderManager.h"
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
    _shaderManager = new ShaderManager();
    _shaderManager->SetDevice(_renderManager->GetDevice());
    _shaderManager->Initialise();

    CreateCube();
    CreatePyramid();
    CreatePlane();

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

void ModelManager::CreateCube() {
    std::vector<SimpleVertex> VertexData = {
        //Position                          //Normal
        { XMFLOAT3(-1.00f,  1.00f, -1.00f), XMFLOAT3(-1.00f,  1.00f, -1.00f)    },
        { XMFLOAT3(1.00f,  1.00f, -1.00f),  XMFLOAT3(1.00f,  1.00f, -1.00f)     },
        { XMFLOAT3(-1.00f, -1.00f, -1.00f), XMFLOAT3(-1.00f, -1.00f, -1.00f)    },
        { XMFLOAT3(1.00f, -1.00f, -1.00f),  XMFLOAT3(1.00f, -1.00f, -1.00f)     },
        { XMFLOAT3(-1.00f,  1.00f, 1.00f),  XMFLOAT3(-1.00f,  1.00f, 1.00f)     },
        { XMFLOAT3(1.00f,  1.00f, 1.00f),   XMFLOAT3(1.00f,  1.00f, 1.00f)      },
        { XMFLOAT3(-1.00f, -1.00f, 1.00f),  XMFLOAT3(-1.00f, -1.00f, 1.00f)     },
        { XMFLOAT3(1.00f, -1.00f, 1.00f),   XMFLOAT3(1.00f, -1.00f, 1.00f)      },
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

    model->SetShader(_shaderManager->GetDefaultShader());

    AddModel(model, "Test Cube");
}

void ModelManager::CreatePyramid() {
    std::vector<SimpleVertex> VertexData = {
        //Position                          //Color             
        { XMFLOAT3(0.00f,  1.00f, 0.00f),   XMFLOAT3(0.00f,  1.00f, 0.00f)      },
        { XMFLOAT3(-1.00f, -1.00f, -1.00f), XMFLOAT3(-1.00f, -1.00f, -1.00f)    },
        { XMFLOAT3(1.00f, -1.00f, -1.00f),  XMFLOAT3(1.00f, -1.00f, -1.00f)     },
        { XMFLOAT3(-1.00f, -1.00f, 1.00f),  XMFLOAT3(-1.00f, -1.00f, 1.00f)     },
        { XMFLOAT3(1.00f, -1.00f, 1.00f),   XMFLOAT3(1.00f, -1.00f, 1.00f)      },
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
    
    model->SetShader(_shaderManager->GetDefaultShader());

    AddModel(model, "Test Pyramid");
}

void ModelManager::CreatePlane() {
    std::vector<SimpleVertex> VertexData = {
        //Position                          //Color             
        { XMFLOAT3(50.00f,  -5.00f, 50.00f),  XMFLOAT3(0.5f, 0.3f, 0.50f)       },
        { XMFLOAT3(-50.00f, -5.00f, -50.00f), XMFLOAT3(0.5f, 0.3f, 0.50f)       },
        { XMFLOAT3(50.00f, -5.00f, -50.00f),  XMFLOAT3(0.5f, 0.3f, 0.50f)       },
        { XMFLOAT3(-50.00f, -5.00f, 50.00f),  XMFLOAT3(0.5f, 0.3f, 0.50f)       },
    };

    std::vector<WORD> IndexData = {
        //Indices
        3,0,1,
        2,1,0,
    };


    Model* model = new Model(_renderManager->GetDevice(), VertexData, IndexData);

    model->SetShader(_shaderManager->GetDefaultShader());

    AddModel(model, "Floor Plane");
}

// Author: Jonathan Davidson (2023)
void ModelManager::LoadModelFromFile(std::string path, std::string modelName) {
    std::ifstream modelFile;

    modelFile.open(path);
    
    std::vector<SimpleVertex> SimpleVerts;
    std::vector<XMFLOAT3> Vertices;
    std::vector<XMFLOAT3> Normals;
    std::vector<XMFLOAT2> Textures;
    std::vector<WORD> Indices;

    if (!modelFile) {
        // throw an error!!!
        return;
    }

    std::string line;
    std::default_random_engine gen;
    std::uniform_real_distribution<float> distribution(0.0, 1.0);

    int indiceCount = 0;
    int vertPos;
    // The spaghetti!! Plan on redoing this later, I can't remember how to read files.
    while (getline(modelFile, line)) {
        std::istringstream stringStream(line);

        std::string type{}, x{}, y{}, z{};

        stringStream >> type >> x >> y >> z;
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
                        simpleVert.Position = Vertices.at(std::stoi(temp.c_str()) - 1);
                    }
                    
                    //if(state == 1) { // vt
                    //    
                    //}
                    
                    if(state == 2) { // vn
                        simpleVert.Normal = Normals.at(std::stoi(temp.c_str()) - 1);
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

}