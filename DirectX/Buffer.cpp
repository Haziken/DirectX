#include "Buffer.h"

MYCODE::Buffer::Buffer(DirectRender& render, UINT bufferType, const void* bufferData, UINT bufferSize)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = bufferSize;
	bd.BindFlags = bufferType;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = bufferData;

	HRESULT hr = S_OK;
	hr = render.GetDevice()->CreateBuffer(&bd, &initData, &buffer);
	if (FAILED(hr)) exit(-1);
}

void MYCODE::Buffer::Bind(DirectRender& render)
{
	
}

ID3D11Buffer* MYCODE::Buffer::GetBuffer()
{
	return buffer;
}
