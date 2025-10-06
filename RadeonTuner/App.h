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
		void SetTopMost(bool topMost);
		void SetContent(FrameworkElement const& content);
		void CreateTrayIcon(HINSTANCE hInstance);
		void CreateWindowXaml(HINSTANCE hInstance);
		void DispatcherInvoke(std::function<void()> const& action);

	private:
		CoreDispatcher _dispatcher = NULL;
		WindowsXamlManager _windowsXamlManager = NULL;
		DesktopWindowXamlSource _desktopWindowXamlSource = NULL;
	};
}