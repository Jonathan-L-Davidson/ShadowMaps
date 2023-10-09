#include "Cube.h"
#include "Renderer.h"

Cube::Cube() {
    return;
}

Cube::~Cube() {
	return;
}

void Cube::Initialise() {
    
    std::vector<SimpleVertex> VertexData = {
        //Position                     //Color             
        { XMFLOAT3(-1.00f,  1.00f, -1.00f), XMFLOAT4(1.0f,  0.0f, 0.0f,  0.0f)},
        { XMFLOAT3(1.00f,  1.00f, -1.00f),  XMFLOAT4(0.0f,  1.0f, 0.0f,  0.0f)},
        { XMFLOAT3(-1.00f, -1.00f, -1.00f), XMFLOAT4(0.0f,  0.0f, 1.0f,  0.0f)},
        { XMFLOAT3(1.00f, -1.00f, -1.00f),  XMFLOAT4(1.0f,  1.0f, 1.0f,  0.0f)},
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
    Shader shaders = _renderManager->GetShaders();
    model->SetVertexShader(shaders.vertexShader);
    model->SetPixelShader(shaders.pixelShader);
    SetModel(model);

}

void Cube::Update(float deltaTime) {
    XMStoreFloat4x4(&_worldPos, XMMatrixIdentity() * XMMatrixRotationZ(2.0f * deltaTime) * XMMatrixRotationY(2.0f * deltaTime));
}