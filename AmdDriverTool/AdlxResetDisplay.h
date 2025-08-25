#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::button_Reset_ColorTemperature_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			slider_Display_ColorTemperature().Value(6500);
		}
		catch (...) {}
	}
}