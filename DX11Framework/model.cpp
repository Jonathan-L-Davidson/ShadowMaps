#include "model.h"
#include "Structures.h"
#include "ShaderManager.h"
#include "TextureManager.h"

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

void Model::SetShader(std::string shaderFile) {
    Shader* shader = _shaderManager->GetShader(shaderFile);
    if(shader != nullptr) {
        _shader = shader;
        return;
    }

    _shaderManager->AddShader(shaderFile);
    shader = _shaderManager->GetShader(shaderFile);

    if (shader == nullptr) {
        return; // Error!
    }

    _shader = shader;

}

void Model::SetupInput(ID3D11DeviceContext* context) {
    //Input Assembler
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ID3D11InputLayout* il = _shaderManager->GetDefaultShader()->GetInputLayout();
    context->IASetInputLayout(il);
}

void Model::SetupTextures(ID3D11DeviceContext* context) {
    Texture* texture = GetTexture();
    _useTexture = false; // Reset to 0 incase we lose our texture later on.

    if (texture != nullptr) {
        ID3D11SamplerState* sampler = texture->GetSampler();
        context->PSSetSamplers(0, 1, &sampler);
        ID3D11ShaderResourceView* textureResource = texture->GetResourceTexture();
        context->PSSetShaderResources(0, 1, &textureResource);
        
        _useTexture = true;
    }
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

void Model::UpdateCBData(ConstantBuffer* cbData) {
    cbData->DiffuseLight = _diffuseLight;
    cbData->DiffuseMaterial = _diffuseMaterial;
    
    cbData->LightPosition = _light.Position;
    cbData->LightRotation = _light.Rotation;
    
    cbData->SpecularLight = _specularLight;
    cbData->SpecularMaterial = _specularMaterial;
    
    cbData->SpecPower = _specPower;
    
    cbData->UseTexture = _useTexture;
}