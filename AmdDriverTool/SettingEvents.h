#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::toggleswitch_Window_Top_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				AppVariables::App.SetTopMost(true);
				textblock_Status().Text(L"Set window on top");
				AVDebugWriteLine(L"Set window on top");
			}
			else
			{
				AppVariables::App.SetTopMost(false);
				textblock_Status().Text(L"Set window not on top");
				AVDebugWriteLine(L"Set window not on top");
			}
		}
		catch (...) {}
	}
}