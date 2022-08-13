#pragma once
#include "DirectRender.h"
#include <vector>
namespace MYCODE
{
	class Buffer
	{
	public:
		Buffer(DirectRender& render, UINT bufferType, const void* bufferData, UINT bufferSize);

		void Bind(DirectRender& render);

		ID3D11Buffer* GetBuffer();

	private:
		ID3D11Buffer* buffer;
	};
}

