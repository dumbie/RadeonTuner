#pragma once
#include "AppVariables.h"
#include "pch.h"
#include "resource.h"
#include "App.h"
#if __has_include("App.g.cpp")
#include "App.g.cpp"
#endif

namespace winrt::RadeonTuner::implementation
{
	//Variables
	HWND _hWnd_MainWindow = NULL;
	HWND _hWnd_XamlWindow = NULL;

	//Constants
	const UINT WM_TRAYICON_CALL = 0x8001;
	const UINT TM_SETTINGS = 0x8002;
	const UINT TM_WEBSITE = 0x8003;
	const UINT TM_EXIT = 0x8004;

	//Application tray callback
	void AppTrayCallback(LPARAM lParam)
	{
		try
		{
			switch (lParam)
			{
			case WM_LBUTTONDBLCLK:
			{
				//Show window in normal state
				ShowWindow(_hWnd_MainWindow, SW_SHOWNORMAL);
				return;
			}
			case WM_RBUTTONUP:
			{
				//Get cursor position
				POINT pointCursor;
				GetCursorPos(&pointCursor);

				//Show tray menu
				HMENU hMenu = CreatePopupMenu();
				InsertMenuW(hMenu, 0, MF_BYPOSITION | MF_STRING, TM_SETTINGS, L"Settings");
				InsertMenuW(hMenu, 1, MF_BYPOSITION | MF_SEPARATOR, NULL, NULL);
				InsertMenuW(hMenu, 2, MF_BYPOSITION | MF_STRING, TM_WEBSITE, L"Website");
				InsertMenuW(hMenu, 3, MF_BYPOSITION | MF_SEPARATOR, NULL, NULL);
				InsertMenuW(hMenu, 4, MF_BYPOSITION | MF_STRING, TM_EXIT, L"Exit");

				//Track tray menu
				SetForegroundWindow(_hWnd_MainWindow);
				TrackPopupMenuEx(hMenu, TPM_RIGHTBUTTON | TPM_LEFTALIGN | TPM_BOTTOMALIGN, pointCursor.x, pointCursor.y, _hWnd_MainWindow, NULL);

				//Destroy tray menu
				DestroyMenu(hMenu);
				return;
			}
			}
		}
		catch (...) {}
	}

	//Application tray click
	void AppTrayClick(WPARAM wParam)
	{
		try
		{
			switch (wParam)
			{
			case TM_SETTINGS:
			{
				//Show window in normal state
				ShowWindow(_hWnd_MainWindow, SW_SHOWNORMAL);
				return;
			}
			case TM_WEBSITE:
			{
				//Open project website
				ShellExecuteW(0, 0, L"https://projects.arnoldvink.com", 0, 0, 0);
				return;
			}
			case TM_EXIT:
			{
				//Exit application
				PostQuitMessage(0);
				return;
			}
			}
		}
		catch (...) {}
	}

	//Application close click
	BOOL AppCloseClick()
	{
		try
		{
			std::optional<bool> CloseTray = AppVariables::Settings.Load<bool>("CloseTray");
			if (CloseTray.has_value() && CloseTray.value())
			{
				AVDebugWriteLine("Closing application to tray.");

				//Show window in hidden state
				ShowWindow(_hWnd_MainWindow, SW_HIDE);
				return 0;
			}
			else
			{
				AVDebugWriteLine("Exiting application.");

				//Exit application
				PostQuitMessage(0);
				return 0;
			}
		}
		catch (...) {}
	}

	//Callbacks
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT messageCode, WPARAM wParam, LPARAM lParam)
	{
		try
		{
			switch (messageCode)
			{
			case WM_TRAYICON_CALL:
				//Handle tray icon callback
				AppTrayCallback(lParam);
				return 0;
			case WM_COMMAND:
			{
				//Handle tray icon click
				AppTrayClick(wParam);
				return 0;
			}
			case WM_CLOSE:
				//Handle app close click
				return AppCloseClick();
			case WM_SIZE:
				//Resize xaml window
				RECT rectClient;
				GetClientRect(hWnd, &rectClient);
				MoveWindow(_hWnd_XamlWindow, 0, 0, rectClient.right, rectClient.bottom, true);
				return 0;
			default:
				return DefWindowProcW(hWnd, messageCode, wParam, lParam);
			}
		}
		catch (...) {}
	}

	//Functions
	App::App() {}

	void App::DispatcherInvoke(std::function<void()> const& action)
	{
		try
		{
			if (_dispatcher == NULL)
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
		catch (...) {}
	}

	void App::SetContent(FrameworkElement const& content)
	{
		try
		{
			if (_desktopWindowXamlSource == NULL)
			{
				return;
			}

			//Set DesktopWindowXamlSource content
			_desktopWindowXamlSource.Content(content);
		}
		catch (...) {}
	}

	void App::SetTopMost(bool topMost)
	{
		try
		{
			if (_desktopWindowXamlSource == NULL)
			{
				return;
			}

			//Set window style
			if (topMost)
			{
				SetWindowPos(_hWnd_MainWindow, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			}
			else
			{
				SetWindowPos(_hWnd_MainWindow, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			}
		}
		catch (...) {}
	}

	void App::CreateTrayIcon(HINSTANCE hInstance)
	{
		try
		{
			//Load tray icon
			HICON hTrayIcon = LoadIconW(hInstance, MAKEINTRESOURCE(ICON_APP));

			//Create tray data
			NOTIFYICONDATA notifyIcon = { };
			notifyIcon.cbSize = sizeof(notifyIcon);
			notifyIcon.hWnd = _hWnd_MainWindow;
			notifyIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
			notifyIcon.uCallbackMessage = WM_TRAYICON_CALL;
			notifyIcon.hIcon = hTrayIcon;

			//Set tray strings
			std::wstring szTrayTip = L"RadeonTuner";
			lstrcpynW(notifyIcon.szTip, szTrayTip.c_str(), 127);

			//Show tray icon
			Shell_NotifyIconW(NIM_ADD, &notifyIcon);
		}
		catch (...) {}
	}

	void App::CreateWindowXaml(HINSTANCE hInstance, bool visible)
	{
		try
		{
			//Initialize for current thread
			winrt::init_apartment(apartment_type::multi_threaded);
			_windowsXamlManager = WindowsXamlManager::InitializeForCurrentThread();
			if (CoreWindow coreWindow = CoreWindow::GetForCurrentThread())
			{
				_dispatcher = coreWindow.Dispatcher();
			}

			//Set window strings
			const LPCWSTR szWindowTitle = L"RadeonTuner";
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
			int windowHeight = 960;
			long dwStyle = WS_VISIBLE | WS_OVERLAPPEDWINDOW;

			_hWnd_MainWindow = CreateWindowW(szWindowClass, szWindowTitle, dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);
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

			//Set xaml window size and location
			MoveWindow(_hWnd_XamlWindow, 0, 0, rectClient.right, rectClient.bottom, true);

			//Show xaml window in normal state
			ShowWindow(_hWnd_XamlWindow, SW_SHOWNORMAL);

			//Hide main window based on setting
			if (!visible)
			{
				ShowWindow(_hWnd_MainWindow, SW_HIDE);
			}

			//Set DesktopWindowXamlSource content
			_desktopWindowXamlSource.Content(MainPage());

			//Create application tray icon
			CreateTrayIcon(hInstance);

			//Window message loop
			MSG msg;
			while (GetMessageW(&msg, NULL, 0, 0))
			{
				try
				{
					TranslateMessage(&msg);
					DispatchMessageW(&msg);
				}
				catch (...) {}
			}
		}
		catch (...) {}
	}
}