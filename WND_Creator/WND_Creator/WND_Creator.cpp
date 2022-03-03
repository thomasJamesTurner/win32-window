#include "WND_Creator.h"
#include <Windows.h>
#include <strsafe.h>


const wchar_t ClassName[] = L"myWindowClass";

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ WND Procedure ~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

LRESULT CALLBACK WndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Msg, wParam, lParam);
	}
	return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Creating the Window Class ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{


	//initializing

	HWND hwnd;
	MSG Msg;


	WNDCLASSEX wc = { };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_VREDRAW | CS_HREDRAW;						//window style
	wc.lpfnWndProc = WndProc;								//pointer to window for this class
	wc.cbClsExtra = 0;										//amount of extra ram given to the window class
	wc.cbWndExtra = 0;										//amount of extra ram given to each window
	wc.hInstance = hInstance;								//the instance (the activator for the exe file)
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//32*32 icon
	wc.hCursor = LoadIcon(NULL, IDC_ARROW);					//sets the cursor to be the generic ARROW
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	   		//sets the window background 
	wc.lpszMenuName = NULL;									//specifies a menu for the window to come from
	wc.lpszClassName = ClassName;							//identifys the ClassName to identify the class
	
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Window Registration Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	int width = 640;
	int height = 480;

	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	AdjustWindowRect(&rect, style, false);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Window Creator ~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	hwnd = CreateWindowExW(
		WS_EX_APPWINDOW,																//window style
		ClassName,																		//the class name of the window
		L"TestWindow",																	//the name of the actual window (using long because its an LPCWSTR and not LPCTSTR)
		WS_OVERLAPPEDWINDOW,															//behavior style of the window
		rect.left, rect.top, rect.right - rect.left, rect.bottom- rect.top,				//x pos, y pos, length, height (but it is the adjusted values)
		NULL, NULL, hInstance, NULL														//parent window, menu, activation(hInstance) and pointer
	);



	//checking for failiure to open
	if (hwnd == NULL)
	{
		WCHAR test[100];
		DWORD errorCode = GetLastError();
		swprintf_s(test,100, L"%d", errorCode);

		MessageBoxW(hwnd,test, L"ERROR:", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, SW_SHOW);								//shows and updates the window
	UpdateWindow(hwnd);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Message Loop ~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessageW(&Msg);
	}

	return Msg.wParam;
};
