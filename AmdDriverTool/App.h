#pragma once
#include "pch.h"
#include "App.g.h"

namespace winrt::AmdDriverTool::implementation
{
	//Classes
	class App
	{
	public:
		App();
		void SetTopMost(bool topMost);
		void SetContent(FrameworkElement const& content);
		void Initialize(HINSTANCE hInstance);
		void DispatcherInvoke(std::function<void()> const& action);

	private:
		CoreDispatcher _dispatcher = NULL;
		WindowsXamlManager _windowsXamlManager = NULL;
		DesktopWindowXamlSource _desktopWindowXamlSource = NULL;
	};
}