#include "DirectRender.h"

MYCODE::DirectRender::DirectRender(MYCODE::Window* win)
{
    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    Rect winSize = win->GetWindowSize();

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = winSize.w;
    sd.BufferDesc.Height = winSize.h;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 75;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = win->GetWindow();
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    HRESULT hr = S_OK;
    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
    {
        driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain(
            NULL, 
            driverType,
            NULL, 
            0, 
            featureLevels, 
            numFeatureLevels,
            D3D11_SDK_VERSION, 
            &sd, 
            &swapChain, 
            &device, 
            &featureLevel, 
            &context);
        if (SUCCEEDED(hr)) break;
    }
    if (FAILED(hr)) exit(-1);

    ID3D11Texture2D* backBuffer = NULL;
    hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
    if (FAILED(hr)) exit(-1);

    hr = device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
    backBuffer->Release();
    if (FAILED(hr)) exit(-1);

    context->OMSetRenderTargets(1, &renderTargetView, NULL);

    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)winSize.w;
    vp.Height = (FLOAT)winSize.h;
    vp.MaxDepth = 1.0f;
    vp.MinDepth = 0.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    context->RSSetViewports(1, &vp);
}

MYCODE::DirectRender::~DirectRender()
{
    context->ClearState();
    renderTargetView->Release();
    swapChain->Release();
    context->Release();
    device->Release();
}

ID3D11Device* MYCODE::DirectRender::GetDevice()
{
    return device;
}

ID3D11DeviceContext* MYCODE::DirectRender::GetContext()
{
    return context;
}

IDXGISwapChain* MYCODE::DirectRender::GetSwapChain()
{
    return swapChain;
}

ID3D11RenderTargetView* MYCODE::DirectRender::GetRenderTargerView()
{
    return renderTargetView;
}

void MYCODE::DirectRender::Render()
{
    float clearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
    context->ClearRenderTargetView(renderTargetView, clearColor);
    //swapChain->Present(0, 0);
}
