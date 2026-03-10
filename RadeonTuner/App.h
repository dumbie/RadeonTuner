#pragma once
#include "pch.h"
#include "App.g.h"

namespace winrt::RadeonTuner::implementation
{
	//Classes
	class App
	{
	public:
		App();
		HWND GetHandle();
		void SetTopMost(bool topMost);
		void SetContent(FrameworkElement const& content);
		void CreateTrayIcon(HINSTANCE hInstance);
		void CreateWindowXaml(HINSTANCE hInstance, bool winVisible, bool winOnTop);
		void DispatcherInvoke(std::function<void()> const& action);
		void Exit(bool forceExit);

	private:
		CoreDispatcher _dispatcher = NULL;
		WindowsXamlManager _windowsXamlManager = NULL;
		DesktopWindowXamlSource _desktopWindowXamlSource = NULL;
	};
}