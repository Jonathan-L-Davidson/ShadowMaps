#include "ModelHelpers.h"
#include <stdexcept>

/// <summary>
/// Contains buffer for vertices with appropriate helpers.
/// </summary>
/// <param name="device"></param>
VertexBuffer::VertexBuffer(ID3D11Device* device) {
	_device = device;
	_vertices = new std::list<SimpleVertex>();
}

VertexBuffer::~VertexBuffer() {
	_buffer->Release();
	_buffer = 0;
	_vertices->clear();
	delete _vertices;
}

void VertexBuffer::SetBuffer(std::list<SimpleVertex> verts) {
	_vertices->assign(verts.begin(),verts.end());
	RefreshBuffer();
}

void VertexBuffer::RefreshBuffer() {
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.ByteWidth = sizeof(_vertices);
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexData = { _vertices };

	hr = _device->CreateBuffer(&vertexBufferDesc, &vertexData, &_buffer);
	if (FAILED(hr)) throw std::invalid_argument("Vertex Buffer failed to refresh/initialise");
}

/// <summary>
/// Contains buffers for indices with appropriate helpers.
/// </summary>
/// <param name="device"></param>
IndexBuffer::IndexBuffer(ID3D11Device* device) {
	_device = device;
	_indices = new std::list<WORD>();
}
IndexBuffer::~IndexBuffer() {
	_buffer->Release();
	_buffer = 0;
	_indices->clear();
	delete _indices;
}

void IndexBuffer::SetBuffer(std::list<WORD> ind) {
	_indices->assign(ind.begin(), ind.end());
	RefreshBuffer();
}

void IndexBuffer::RefreshBuffer() {
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.ByteWidth = sizeof(_indices);
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA indexData = { _indices };

	hr = _device->CreateBuffer(&indexBufferDesc, &indexData, &_buffer);
	if (FAILED(hr)) throw std::invalid_argument("Index Buffer failed to refresh/initialise");
}

/// <summary>
/// Model Buffer, the wrapper to contain both Index and Vertex buffers to be managed.
/// </summary>
/// <param name="device"></param>
ModelBuffer::ModelBuffer(ID3D11Device* device) {
	_vBuffer = new VertexBuffer(device);
	_iBuffer = new IndexBuffer(device);
}

ModelBuffer::ModelBuffer(ID3D11Device* device, std::list<SimpleVertex> verts, std::list<WORD> indices) {
	_vBuffer = new VertexBuffer(device);
	_iBuffer = new IndexBuffer(device);

	_vBuffer->SetBuffer(verts);
	_iBuffer->SetBuffer(indices);
}
ModelBuffer::~ModelBuffer() {
	delete _vBuffer;
	delete _iBuffer;

	_vBuffer = 0;
	_iBuffer = 0;
}
