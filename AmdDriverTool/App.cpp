#pragma once
#include "pch.h"
#include "resource.h"
#include "App.h"
#if __has_include("App.g.cpp")
#include "App.g.cpp"
#endif

namespace winrt::AmdDriverTool::implementation
{
	//Variables
	HWND _hWnd_MainWindow = nullptr;
	HWND _hWnd_XamlWindow = nullptr;

	//Callbacks
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT messageCode, WPARAM wParam, LPARAM lParam)
	{
		switch (messageCode)
		{
		case WM_PAINT:
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_CREATE:
			return 0;
		case WM_SIZE:
			RECT rectClient;
			GetClientRect(hWnd, &rectClient);
			MoveWindow(_hWnd_XamlWindow, 0, 0, rectClient.right, rectClient.bottom, true);
			return 0;
		default:
			return DefWindowProcW(hWnd, messageCode, wParam, lParam);
		}
	}

	//Functions
	App::App() {}

	void App::DispatcherInvoke(std::function<void()> const& action)
	{
		if (_dispatcher == nullptr)
		{
			return;
		}

		if (_dispatcher.HasThreadAccess())
		{
			action();
		}
		else
		{
			_dispatcher.RunAsync(CoreDispatcherPriority::Normal, action);
		}
	}

	void App::SetContent(UIElement const& content)
	{
		if (_desktopWindowXamlSource == nullptr)
		{
			return;
		}

		//Set DesktopWindowXamlSource content
		_desktopWindowXamlSource.Content(content);
	}

	void App::Initialize(HINSTANCE hInstance)
	{
		//Initialize for current thread
		winrt::init_apartment(apartment_type::multi_threaded);
		_windowsXamlManager = WindowsXamlManager::InitializeForCurrentThread();
		if (CoreWindow coreWindow = CoreWindow::GetForCurrentThread())
		{
			_dispatcher = coreWindow.Dispatcher();
		}

		//Set window strings
		const LPCWSTR szWindowTitle = L"AMD Driver Tool";
		const LPCWSTR szWindowClass = L"MainWindow";

		//Load window icon
		HICON hWindowIcon = LoadIconW(hInstance, MAKEINTRESOURCE(ICON_APP));

		//Register window class
		WNDCLASSEX windowClass = { };
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.lpfnWndProc = WindowProc;
		windowClass.hInstance = hInstance;
		windowClass.lpszClassName = szWindowClass;
		windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME);
		windowClass.hIcon = hWindowIcon;
		if (RegisterClassExW(&windowClass) == NULL)
		{
			MessageBoxW(NULL, L"RegisterClassExW failed", L"Error", NULL);
			return;
		}

		//Create main window
		int windowWidth = 1280;
		int windowHeight = 900;
		_hWnd_MainWindow = CreateWindowW(szWindowClass, szWindowTitle, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);
		if (_hWnd_MainWindow == NULL)
		{
			MessageBoxW(NULL, L"CreateWindowW failed", L"Error", NULL);
			return;
		}

		//Create desktop window xaml source
		_desktopWindowXamlSource = DesktopWindowXamlSource();

		//Get native desktop window xaml source
		auto desktopWindowXamlSourceNative = _desktopWindowXamlSource.as<IDesktopWindowXamlSourceNative2>();

		//Attach DesktopWindowXamlSource to main window
		HRESULT hResult = desktopWindowXamlSourceNative->AttachToWindow(_hWnd_MainWindow);
		if (FAILED(hResult))
		{
			MessageBoxW(NULL, L"AttachToWindow failed", L"Error", NULL);
			return;
		}

		//Get DesktopWindowXamlSource window handle
		hResult = desktopWindowXamlSourceNative->get_WindowHandle(&_hWnd_XamlWindow);
		if (FAILED(hResult))
		{
			MessageBoxW(NULL, L"XamlGetWindowHandle failed", L"Error", NULL);
			return;
		}

		//Update DesktopWindowXamlSource window size
		RECT rectClient;
		GetClientRect(_hWnd_MainWindow, &rectClient);
		SetWindowPos(_hWnd_XamlWindow, 0, 0, 0, rectClient.right, rectClient.bottom, SWP_SHOWWINDOW);

		//Set DesktopWindowXamlSource content
		_desktopWindowXamlSource.Content(MainPage());

		//Window message loop
		MSG msg;
		while (GetMessageW(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
}