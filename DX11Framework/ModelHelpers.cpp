#include "ModelHelpers.h"

Buffer::Buffer(ID3D11Device* device) {
	_device = device;
	_buffer = new std::list<XMFLOAT3>();
}
Buffer::~Buffer() {
	delete _buffer;
	_buffer = 0;
}

void Buffer::SetBuffer(Buffer buff) {
	_buffer->assign(buff.GetBufferFloat3()->begin(), buff.GetBufferFloat3()->end());
	
	RefreshBuffer();
}

ModelBuffer::ModelBuffer(ID3D11Device* device) {
	_vBuffer = new Buffer(device);
	_iBuffer = new Buffer(device);
}

ModelBuffer::ModelBuffer(ID3D11Device* device, Buffer vBuffer, Buffer iBuffer) {
	_vBuffer = new Buffer(device);
	_iBuffer = new Buffer(device);

	_vBuffer->SetBuffer(vBuffer);
	_iBuffer->SetBuffer(iBuffer);
}
ModelBuffer::~ModelBuffer() {
	delete _vBuffer;
	delete _iBuffer;

	_vBuffer = 0;
	_iBuffer = 0;
}
