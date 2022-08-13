#pragma once
#include <d3dcompiler.h>
#include "DirectRender.h"

namespace MYCODE
{
	class Shader
	{
	public:
		Shader(DirectRender& render, LPCWSTR pathToVS, LPCWSTR pathToPS, LPCSTR shaderModel);

		ID3D11VertexShader* GetVertexShader();
		ID3D11PixelShader* GetPixelShader();
		ID3DBlob* GetVertexBlob();
		ID3DBlob* GetPixelBlob();

	private:
		HRESULT CompileShaderFromFile(LPCWSTR path, LPCSTR entryPoint, LPCSTR sharedModel, ID3DBlob*& blob);

		ID3DBlob* vertexBlob;
		ID3D11VertexShader* vertexShader;
		ID3DBlob* pixelBlob;
		ID3D11PixelShader* pixelShader;
	};
}