#include "model.h"
#include "Structures.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Transform.h"

Model::Model(ID3D11Device* device) {
    _modelBuffer = new ModelBuffer(device);
    transform = new Transform();
}

Model::Model(ID3D11Device* device, std::vector<SimpleVertex> verts, std::vector<DWORD> indices) {
    _modelBuffer = new ModelBuffer(device, verts, indices);
    transform = new Transform();

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
    _useTexture = 0; // Reset to 0 incase we lose our texture later on.

    if (texture != nullptr) {
        ID3D11SamplerState* sampler = texture->GetSampler();
        context->PSSetSamplers(0, 1, &sampler);
        ID3D11ShaderResourceView* textureResource;
        if (texture->hasDiffuse) {
            textureResource = texture->GetResourceTexture(TextureType::DIFFUSE);
            context->PSSetShaderResources(0, 1, &textureResource);
        }
        if (texture->hasDisplacement) {
            textureResource = texture->GetResourceTexture(TextureType::DISPLACEMENT);
            context->PSSetShaderResources(1, 1, &textureResource);
        }
        if (texture->hasNormal) {
            textureResource = texture->GetResourceTexture(TextureType::NORMAL);
            context->PSSetShaderResources(2, 1, &textureResource);
        }
        if (texture->hasSpecular) {
            textureResource = texture->GetResourceTexture(TextureType::SPECULAR);
            context->PSSetShaderResources(3, 1, &textureResource);
        }

        _useTexture = 1;
    }
}

void Model::Render(ID3D11DeviceContext* context) {

    //Set object variables and draw
    UINT stride = { sizeof(SimpleVertex) };
    UINT offset = 0;
    ID3D11Buffer* vBuffer = _modelBuffer->GetVertBuffer()->GetBuffer();
    context->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);
    ID3D11Buffer* iBuffer = _modelBuffer->GetIndBuffer()->GetBuffer();
    context->IASetIndexBuffer(iBuffer, DXGI_FORMAT_R32_UINT, 0);

    context->VSSetShader(_shader->GetVertexShader(), nullptr, 0);
    context->PSSetShader(_shader->GetPixelShader(), nullptr, 0);

    context->DrawIndexed(GetIndices(), 0, 0);
}

void Model::UpdateCBData(ConstantBuffer* cbData) {
    cbData->DiffuseMaterial = _diffuseMaterial;
    cbData->SpecularMaterial = _specularMaterial;

    cbData->UseTexture = _useTexture;
    
    if (_useTexture) {
        cbData->UseDiffuse = GetTexture()->hasDiffuse;
        cbData->UseDisplacement = GetTexture()->hasDisplacement;
        cbData->UseNormal = GetTexture()->hasNormal;
        cbData->UseSpecular = GetTexture()->hasSpecular;
    }
}