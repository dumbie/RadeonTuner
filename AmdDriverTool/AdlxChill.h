#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::toggleswitch_Chill_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get chill settings
		IADLX3DChillPtr d3dChill;
		res = d3dSettingSrv->GetChill(gpuInfo, &d3dChill);

		if (sender.as<ToggleSwitch>().IsOn())
		{
			res = d3dChill->SetEnabled(true);
			textBox_Chill_Min().IsEnabled(true);
			textBox_Chill_Max().IsEnabled(true);
			textblock_Status().Text(L"Chill enabled");
			AVDebugWriteLine("Chill is enabled");
		}
		else
		{
			res = d3dChill->SetEnabled(false);
			textBox_Chill_Min().IsEnabled(false);
			textBox_Chill_Max().IsEnabled(false);
			textblock_Status().Text(L"Chill disabled");
			AVDebugWriteLine("Chill is disabled");
		}
	}

	void MainPage::textBox_Chill_Min_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get chill value
		auto newValue = sender.as<TextBox>().Text();

		//Check if value is empty
		if (newValue.empty()) { return; }

		//Set chill settings
		IADLX3DChillPtr d3dChill;
		res = d3dSettingSrv->GetChill(gpuInfo, &d3dChill);
		res = d3dChill->SetMinFPS(hstring_to_int(newValue));
		if (!ADLX_SUCCEEDED(res))
		{
			//Set result
			textBox_Chill_Min().BorderBrush(SolidColorBrush(Windows::UI::Colors::Red()));
			textblock_Status().Text(L"Failed setting chill fps");
			AVDebugWriteLine(L"Failed setting chill fps");
		}
		else
		{
			//Set result
			textBox_Chill_Min().BorderBrush(SolidColorBrush(Windows::UI::Colors::Green()));
			textblock_Status().Text(L"Chill minimum set to " + newValue);
			AVDebugWriteLine(L"Chill minimum set to " + newValue);
		}
	}

	void MainPage::textBox_Chill_Max_TextChanged(IInspectable const& sender, TextChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get chill value
		auto newValue = sender.as<TextBox>().Text();

		//Check if value is empty
		if (newValue.empty()) { return; }

		//Set chill setting
		IADLX3DChillPtr d3dChill;
		res = d3dSettingSrv->GetChill(gpuInfo, &d3dChill);
		res = d3dChill->SetMaxFPS(hstring_to_int(newValue));
		if (!ADLX_SUCCEEDED(res))
		{
			//Set result
			textBox_Chill_Max().BorderBrush(SolidColorBrush(Windows::UI::Colors::Red()));
			textblock_Status().Text(L"Failed setting chill fps");
			AVDebugWriteLine(L"Failed setting chill fps");
		}
		else
		{
			//Set result
			textBox_Chill_Max().BorderBrush(SolidColorBrush(Windows::UI::Colors::Green()));
			textblock_Status().Text(L"Chill maximum set to " + newValue);
			AVDebugWriteLine(L"Chill maximum set to " + newValue);
		}
	}
}