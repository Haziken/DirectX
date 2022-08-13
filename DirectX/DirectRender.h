#pragma once

#include <d3d11.h>	

#include "Window.h"

namespace MYCODE
{
	class DirectRender
	{
	public:
		DirectRender(Window* win);
		~DirectRender();

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetContext();
		IDXGISwapChain* GetSwapChain();
		ID3D11RenderTargetView* GetRenderTargerView();

		void Render();

	private:
		D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;
		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
		ID3D11Device* device = NULL;
		ID3D11DeviceContext* context = NULL;
		IDXGISwapChain* swapChain = NULL;
		ID3D11RenderTargetView* renderTargetView = NULL;
	};
}