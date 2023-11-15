#include "ModelHelpers.h"
#include <stdexcept>

// For context to this messed up solution, using std::lists or std::vectors, they often pass pointers to the buffer instead of the data.
// So I've made it so it creates a new pointer array and copies the list, this can be costly, but aslong as we're not loading models during gameplay,
// this wouldn't be an issue.

/// <summary>
/// Contains buffer for vertices with appropriate helpers.
/// </summary>
/// <param name="device"></param>
VertexBuffer::VertexBuffer(ID3D11Device* device) {
	_device = device;
	_vertices = new std::vector<SimpleVertex>();
}

VertexBuffer::~VertexBuffer() {
	_buffer->Release();
	_vertices->clear();
	delete _vertices;
}

void VertexBuffer::SetBuffer(std::vector<SimpleVertex> verts) {
	_vertices->assign(verts.begin(),verts.end());
	_vertices->reserve(_vertices->size());
	RefreshBuffer();
}

void VertexBuffer::RefreshBuffer() {
	HRESULT hr = S_OK;

	const int vertexSize = _vertices->size();
	SimpleVertex* vertexArray = new SimpleVertex[vertexSize];
	std::copy(_vertices->begin(), _vertices->end(), vertexArray);


	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.ByteWidth = sizeof(SimpleVertex) * vertexSize;
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// Future me, do not initialise subresource data and pass it the array immediately, use pSysMem and pass the first in list as junk data will be sent instead.
	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(vertexData));

	vertexData.pSysMem = &vertexArray[0];
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	hr = _device->CreateBuffer(&vertexBufferDesc, &vertexData, &_buffer);
	if (FAILED(hr)) throw std::invalid_argument("Vertex Buffer failed to refresh/initialise");
	
	delete[] vertexArray;

}

/// <summary>
/// Contains buffers for indices with appropriate helpers.
/// </summary>
/// <param name="device"></param>
IndexBuffer::IndexBuffer(ID3D11Device* device) {
	_device = device;
	_indices = new std::vector<DWORD>();
}
IndexBuffer::~IndexBuffer() {
	_buffer->Release();
	_indices->clear();
	delete _indices;
}

void IndexBuffer::SetBuffer(std::vector<DWORD> ind) {
	_indices->assign(ind.begin(), ind.end());
	_indices->reserve(_indices->size());


	RefreshBuffer();
}

void IndexBuffer::RefreshBuffer() {
	HRESULT hr = S_OK;

	const int indiceSize = _indices->size();
	DWORD* indiceArray = new DWORD[indiceSize];
	std::copy(_indices->begin(), _indices->end(), indiceArray);

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.ByteWidth = sizeof(DWORD) * indiceSize;
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// Future me, do not initialise subresource data and pass it the array immediately, use pSysMem and pass the first in list as junk data will be sent instead.
	D3D11_SUBRESOURCE_DATA indexData;
	ZeroMemory(&indexData, sizeof(indexData));

	indexData.pSysMem = &indiceArray[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	hr = _device->CreateBuffer(&indexBufferDesc, &indexData, &_buffer);
	if (FAILED(hr)) throw std::invalid_argument("Index Buffer failed to refresh/initialise");

	delete[] indiceArray;
}

/// <summary>
/// Model Buffer, the wrapper to contain both Index and Vertex buffers to be managed.
/// </summary>
/// <param name="device"></param>
ModelBuffer::ModelBuffer(ID3D11Device* device) {
	_vBuffer = new VertexBuffer(device);
	_iBuffer = new IndexBuffer(device);
}

ModelBuffer::ModelBuffer(ID3D11Device* device, std::vector<SimpleVertex> verts, std::vector<DWORD> indices) {
	_vBuffer = new VertexBuffer(device);
	_iBuffer = new IndexBuffer(device);

	_vBuffer->SetBuffer(verts);
	_iBuffer->SetBuffer(indices);
}
ModelBuffer::~ModelBuffer() {
	delete _vBuffer;
	delete _iBuffer;
}
