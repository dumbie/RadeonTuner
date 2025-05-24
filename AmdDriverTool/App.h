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
		void SetContent(UIElement const& content);
		void Initialize(HINSTANCE hInstance);
		void DispatcherInvoke(std::function<void()> const& action);

	private:
		CoreDispatcher _dispatcher = nullptr;
		WindowsXamlManager _windowsXamlManager = nullptr;
		DesktopWindowXamlSource _desktopWindowXamlSource = nullptr;
	};
}