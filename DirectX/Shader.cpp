#include "Shader.h"

MYCODE::Shader::Shader(DirectRender& render, LPCWSTR pathToVS, LPCWSTR pathToPS, LPCSTR shaderModel)
{
	HRESULT hr = S_OK;
	hr = CompileShaderFromFile(pathToVS, "VS", "vs_4_0", vertexBlob);
	if (FAILED(hr)) exit(-1);
	hr = render.GetDevice()->CreateVertexShader(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), NULL, &vertexShader);
	if (FAILED(hr)) exit(-1);

	hr = CompileShaderFromFile(pathToPS, "PS", "ps_4_0", pixelBlob);
	if (FAILED(hr)) exit(-1);
	hr = render.GetDevice()->CreatePixelShader(pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), NULL, &pixelShader);
	if (FAILED(hr)) exit(-1);
}

ID3D11VertexShader* MYCODE::Shader::GetVertexShader()
{
	return vertexShader;
}

ID3D11PixelShader* MYCODE::Shader::GetPixelShader()
{
	return pixelShader;
}

ID3DBlob* MYCODE::Shader::GetVertexBlob()
{
	return vertexBlob;
}

ID3DBlob* MYCODE::Shader::GetPixelBlob()
{
	return pixelBlob;
}

HRESULT MYCODE::Shader::CompileShaderFromFile(LPCWSTR path, LPCSTR entryPoint, LPCSTR sharedModel, ID3DBlob*& blob)
{
	HRESULT hr = S_OK;
	DWORD dwShaderFlag = D3DCOMPILE_ENABLE_STRICTNESS;
	ID3DBlob* errorBlob = NULL;
	const D3D_SHADER_MACRO defines[] = {
		"EXAMPLE_DEFINE",
		"1",
		NULL,
		NULL
	};
	hr = D3DCompileFromFile(
		path,
		defines,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint,
		sharedModel,
		dwShaderFlag,
		0,
		&blob,
		&errorBlob);
	if (FAILED(hr))
	{
		if (errorBlob)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
		}
		if (blob) blob->Release();
		return hr;
	}
	if (errorBlob) errorBlob->Release();
	return hr;
}
