#pragma once

#if !defined(MODELHELPER_CLASS)
#define MODELHELPER_CLASS

#include "DX11Framework.h"
#include <list>

class ModelHelpers {

};

class Buffer {
public:
	Buffer();
	~Buffer();
	
	void SetBuffer(Buffer buff);

	std::list<XMFLOAT3>* GetBuffer() { return _buffer; };
	int GetCount() { return _buffer->size(); };

private:
	std::list<XMFLOAT3>* _buffer;
};

class ModelBuffer {
public:
	ModelBuffer();
	ModelBuffer(Buffer vBuffer, Buffer iBuffer);
	~ModelBuffer();

	Buffer* GetVertBuffer()		{ return _vBuffer; };
	Buffer* GetIndBuffer() { return _iBuffer; };

private:
	Buffer* _vBuffer; // Vertex Buffer
	Buffer* _iBuffer; // Index Buffer
};

#endif