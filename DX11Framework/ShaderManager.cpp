#include "ShaderManager.h"
#include "Structures.h"

Shader::Shader() {

}

Shader::~Shader() {
	if (_vertexShader)	DELETED3D(_vertexShader);

	if (_pixelShader)	DELETED3D(_pixelShader);
}

ID3D11VertexShader* Shader::GetVertexShader() {
	if (_vertexShader) {
		return _vertexShader;
	}
	return _default->GetVertexShader();
}
ID3D11PixelShader* Shader::GetPixelShader() {
	if (_pixelShader) {
		return _pixelShader;
	}
	return _default->GetPixelShader();
}


ShaderManager::ShaderManager() {
	_shaders = new std::map<std::string, Shader*>();
}
ShaderManager::~ShaderManager() {
	delete _shaders;
}

void ShaderManager::Initialise() {

    HRESULT hr = S_OK;


    D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA,   0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
    };

    hr = _device->CreateInputLayout(inputElementDesc, ARRAYSIZE(inputElementDesc), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &_inputLayout);
    if (FAILED(hr)) return;


	CreateDefaultShader();
}

void ShaderManager::CreateDefaultShader() {
	CreateShaderFromFile("Default")
}

Shader* ShaderManager::GetShader(std::string id) {
	return _shaders->find(id)->second;
}

void ShaderManager::AddShader(Shader* shader, std::string id) {
	_shaders->insert(std::make_pair(id, shader));
}

void ShaderManager::AddShader(std::string id) {
	if (_shaders->find(id)->second != nullptr)
		return; // Already created.

	CreateShaderFromFile(id);
}

void ShaderManager::RemoveShader(std::string id) {
	_shaders->erase(id);
}

void ShaderManager::CreateShaderFromFile(std::string id) {

    Shader shader;

    HRESULT hr = S_OK;
    ID3DBlob* errorBlob;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* vsBlob;
    
    id.append(".hlsl");

    std::wstring idTemp = std::wstring(id.begin(), id.end());
    LPCWSTR path = idTemp.c_str();
    
    
    hr = D3DCompileFromFile(path, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS_main", "vs_5_0", dwShaderFlags, 0, &vsBlob, &errorBlob);
    if (FAILED(hr)) {
        // TODO Check if vertex shader exists.
        shader.SetVertexShader(GetDefaultShader()->GetVertexShader());
    }
    else {

        hr = _device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &*shader.GetVertexShader());
        if (FAILED(hr)) return;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ID3DBlob* psBlob;

    hr = D3DCompileFromFile(path, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS_main", "ps_5_0", dwShaderFlags, 0, &psBlob, &errorBlob);
    if (FAILED(hr)) {
        // TODO Check if pixel shader exists.
        shader.SetPixelShader(GetDefaultShader()->GetPixelShader());
    }
    else {
        hr = _device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &*shader.GetPixelShader());
        if (FAILED(hr)) return;
    }
    vsBlob->Release();
    psBlob->Release();

    Shader* S = new Shader(shader);
    AddShader(S, id);

}
