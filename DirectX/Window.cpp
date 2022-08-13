#include "Window.h"

MYCODE::Window::Window(
	LPCWSTR title, 
	int x, int y, int w, int h, 
	HINSTANCE hInstance, 
	WNDPROC wndproc, 
	HICON hIcon, 
	HCURSOR hCursor, 
	HBRUSH hbrush, 
	LPCWSTR menuName, 
	HICON hIconSm,
	int clsExtra,
	int wndExtra)
	: hInstance(hInstance)
{
	WNDCLASSEX win{0};
	win.cbSize = sizeof(WNDCLASSEX);
	win.style = CS_HREDRAW | CS_VREDRAW;
	win.lpfnWndProc = wndproc;
	win.cbClsExtra = 0;
	win.cbWndExtra = 0;
	win.hInstance = hInstance;
	win.hIcon = hIcon;
	win.hCursor = hCursor;
	win.hbrBackground = hbrush;
	win.lpszMenuName = menuName;
	win.lpszClassName = L"MYCLASS";
	win.hIconSm = hIconSm;

	if (!RegisterClassEx(&win)) exit(-1);

	RECT rc = { x, y, w, h };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	window = CreateWindow(L"MYCLASS", L"TEST", WS_OVERLAPPEDWINDOW, x, y, w, h, NULL, NULL, hInstance, NULL);
	if (!window) exit(-1);
	ShowWindow(window, SW_SHOW);
	UpdateWindow(window);
}

HWND MYCODE::Window::GetWindow()
{
	return window;
}

Rect MYCODE::Window::GetWindowSize()
{
	RECT rc;
	GetClientRect(window, &rc);
	return Rect(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
}

int MYCODE::Window::Run()
{
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

LRESULT MYCODE::Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		return 0;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
