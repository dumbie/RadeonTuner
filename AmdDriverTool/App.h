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

	private:
		WindowsXamlManager _windowsXamlManager = nullptr;
		DesktopWindowXamlSource _desktopWindowXamlSource = nullptr;
	};
}