#include "model.h"
#include "ShaderManager.h"

Model::Model(ID3D11Device* device) {
    _modelBuffer = new ModelBuffer(device);
}

Model::Model(ID3D11Device* device, std::vector<SimpleVertex> verts, std::vector<WORD> indices) {
    _modelBuffer = new ModelBuffer(device, verts, indices);
}

Model::~Model() {
    delete _modelBuffer; // TODO Make model buffer manager delete models instead.
    _shader = nullptr;
    _shaderManager = nullptr;
}

void Model::SetupInput(ID3D11DeviceContext* context) {
    //Input Assembler
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->IASetInputLayout(_shaderManager->GetInputLayout());
}

void Model::Render(ID3D11DeviceContext* context) {
    //Set object variables and draw
    UINT stride = { sizeof(SimpleVertex) };
    UINT offset = 0;
    ID3D11Buffer* vBuffer = _modelBuffer->GetVertBuffer()->GetBuffer();
    context->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);
    ID3D11Buffer* iBuffer = _modelBuffer->GetIndBuffer()->GetBuffer();
    context->IASetIndexBuffer(iBuffer, DXGI_FORMAT_R16_UINT, 0);

    context->VSSetShader(_shader->GetVertexShader(), nullptr, 0);
    context->PSSetShader(_shader->GetPixelShader(), nullptr, 0);

    context->DrawIndexed(GetIndices(), 0, 0);
}