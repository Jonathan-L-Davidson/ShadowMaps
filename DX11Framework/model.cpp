#include "model.h"

Model::Model() {

}

Model::~Model() {

}

void Model::Render(ID3D11DeviceContext* context) {
    //Set object variables and draw
    UINT stride = { sizeof(SimpleVertex) };
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, _modelBuffer->GetVertBuffer()->GetBuffer(), &stride, &offset);
    context->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R16_UINT, 0);

    context->VSSetShader(_vertexShader, nullptr, 0);
    context->PSSetShader(_pixelShader, nullptr, 0);

    context->DrawIndexed(GetIndices(), 0, 0);
}