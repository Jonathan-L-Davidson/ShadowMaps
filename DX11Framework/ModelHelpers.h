#pragma once

#if !defined(MODELHELPER_CLASS)
#define MODELHELPER_CLASS

#include "DX11Framework.h"
#include <list>

class ModelHelpers {

};

class Buffer {
public:
	Buffer(ID3D11Device* device);
	~Buffer();
	
	void SetBuffer(Buffer buff);

	std::list<XMFLOAT3>* GetBufferFloat3() { return _buffer; };
	ID3D11Buffer* GetBuffer() { return _xBuffer; };
	int GetCount() { return _buffer->size(); };

	void RefreshBuffer();
private:
	ID3D11Device* _device;
	ID3D11Buffer* _xBuffer; // DirectX buffer

	std::list<XMFLOAT3>* _buffer; // Our own independant buffer system so we can read/write easily
};

class ModelBuffer {
public:
	ModelBuffer(ID3D11Device* device);
	ModelBuffer(ID3D11Device* device, Buffer vBuffer, Buffer iBuffer);
	~ModelBuffer();

	Buffer* GetVertBuffer()		{ return _vBuffer; };
	Buffer* GetIndBuffer() { return _iBuffer; };

private:
	Buffer* _vBuffer; // Vertex Buffer
	Buffer* _iBuffer; // Index Buffer
};

#endif