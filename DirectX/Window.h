#pragma once

#include <Windows.h>
#include <functional>
#include "Utils.h"

namespace MYCODE
{
	class Window
	{
	public:
		Window(
			LPCWSTR title,
			int x, int y, int w, int h,
			HINSTANCE hInstance = NULL,
			WNDPROC wndproc = WindowProc,
			HICON hIcon = NULL,
			HCURSOR hCursor = LoadCursor(NULL, IDC_ARROW),
			HBRUSH hbrush = (HBRUSH)(COLOR_WINDOW + 1),
			LPCWSTR menuName = NULL,
			HICON hIconSm = LoadIcon(NULL, (LPCTSTR)IDI_QUESTION),
			int clsExtra = 0,
			int wndExtra = 0);

		Window(Window&&) = delete;
		Window& operator=(Window&&) = delete;

		HWND GetWindow();
		Rect GetWindowSize();

		int Run();

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		HINSTANCE hInstance = NULL;
		HWND window = nullptr;
		MSG msg{ 0 };
	};
}
