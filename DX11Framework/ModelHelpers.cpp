#include "ModelHelpers.h"

Buffer::Buffer() {
	_buffer = new std::list<XMFLOAT3>();
}
Buffer::~Buffer() {
	delete _buffer;
	_buffer = 0;
}

void Buffer::SetBuffer(Buffer buff) {
	_buffer->assign(buff.GetBuffer()->begin(), buff.GetBuffer()->end());
}

ModelBuffer::ModelBuffer() {
	_vBuffer = new Buffer();
	_iBuffer = new Buffer();
}

ModelBuffer::ModelBuffer(Buffer vBuffer, Buffer iBuffer) {
	ModelBuffer();
	_vBuffer->SetBuffer(vBuffer);
	_iBuffer->SetBuffer(iBuffer);
}
ModelBuffer::~ModelBuffer() {
	delete _vBuffer;
	delete _iBuffer;

	_vBuffer = 0;
	_iBuffer = 0;
}
