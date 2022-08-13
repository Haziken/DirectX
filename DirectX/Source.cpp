//#include "Window.h"
#include "DirectRender.h"
#include "Buffer.h"
#include "Shader.h"
#include <Windows.h>
#include <DirectXMath.h>

using namespace MYCODE;

struct SimpleVertex
{
	 DirectX::XMFLOAT3 Pos;
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmpLine, int nCmdShow)
{

	Window win(L"TEST", 100, 100, 800, 600);
	DirectRender ren(&win);
	MSG msg{};

	ID3D11InputLayout* lay;


	Shader sh(ren, L"VS.fx", L"PS.fx", "vs_4_0");

	//Buffer(ren, )

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	UINT numEl = ARRAYSIZE(layout);

	HRESULT hr = S_OK;

	hr = ren.GetDevice()->CreateInputLayout(
		layout, 
		numEl, 
		sh.GetVertexBlob()->GetBufferPointer(), 
		sh.GetVertexBlob()->GetBufferSize(), 
		&lay);

	ren.GetContext()->IASetInputLayout(lay);

	SimpleVertex ver[] =
	{
		DirectX::XMFLOAT3(0.0f, 0.5f, 0.5f),
		DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f),
		DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f)
	};

	Buffer buf(ren, D3D11_BIND_VERTEX_BUFFER, ver, sizeof(SimpleVertex) * 3);

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	ID3D11Buffer* b = buf.GetBuffer();
	ren.GetContext()->IASetVertexBuffers(0, 1, &b, &stride, &offset);
	
	ren.GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			ren.Render();

			ren.GetContext()->VSSetShader(sh.GetVertexShader(), NULL, 0);
			ren.GetContext()->PSSetShader(sh.GetPixelShader(), NULL, 0);

			ren.GetContext()->Draw(3, 0);

			ren.GetSwapChain()->Present(0,0);
		}
	}

	return msg.wParam;
}