#pragma once

#include "DX11Framework.h"

//class Buffer {
//public:
//	Buffer(ID3D11Device* device);
//	~Buffer();
//	
//	void SetBuffer(Buffer buff);
//
//	std::list<XMFLOAT3>* GetBufferFloat3() { return _buffer; };
//	ID3D11Buffer* GetBuffer() { return _xBuffer; };
//	int GetCount() { return _buffer->size(); };
//
//	void RefreshBuffer();
//private:
//	ID3D11Device* _device;
//	ID3D11Buffer* _xBuffer; // DirectX buffer
//
//	std::list<XMFLOAT3>* _buffer; // Our own independant buffer system so we can read/write easily
//};

class VertexBuffer {
public:
	VertexBuffer(ID3D11Device* device);
	~VertexBuffer();
	
	void SetBuffer(std::list<SimpleVertex>& verts);

	ID3D11Buffer* GetBuffer()					{ return _buffer; };
	int GetCount()								{ return _vertices->size(); };
	std::list<SimpleVertex>* GetVertices()		{ return _vertices; };

	void RefreshBuffer();
private:
	ID3D11Device* _device;
	ID3D11Buffer* _buffer; // DirectX buffer

	std::list<SimpleVertex>* _vertices;

};

class IndexBuffer {
public:
	IndexBuffer(ID3D11Device* device);
	~IndexBuffer();

	void SetBuffer(std::list<WORD> indices);

	ID3D11Buffer* GetBuffer() { return _buffer; };
	int GetCount() { return _indices->size(); };
	std::list<WORD>* GetIndices() { return _indices; };

	void RefreshBuffer();
private:
	ID3D11Device* _device;
	ID3D11Buffer* _buffer; // DirectX buffer

	std::list<WORD>* _indices;
};

class ModelBuffer {
public:
	ModelBuffer(ID3D11Device* device);
	ModelBuffer(ID3D11Device* device, std::list<SimpleVertex> verts, std::list<WORD> indices);
	~ModelBuffer();

	VertexBuffer* GetVertBuffer()	{ return _vBuffer; };
	IndexBuffer* GetIndBuffer() { return _iBuffer; };

private:
	VertexBuffer* _vBuffer; // Vertex Buffer
	IndexBuffer* _iBuffer; // Index Buffer
};
