#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::toggleswitch_RadeonChill_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get chill settings
		IADLX3DChillPtr d3dChill;
		res = d3dSettingSrv->GetChill(gpuInfo, &d3dChill);

		if (sender.as<ToggleSwitch>().IsOn())
		{
			res = d3dChill->SetEnabled(true);
			slider_RadeonChill_Max().IsEnabled(true);
			slider_RadeonChill_Max().IsEnabled(true);
			textblock_Status().Text(L"Chill enabled");
			AVDebugWriteLine("Chill is enabled");
		}
		else
		{
			res = d3dChill->SetEnabled(false);
			slider_RadeonChill_Max().IsEnabled(false);
			slider_RadeonChill_Max().IsEnabled(false);
			textblock_Status().Text(L"Chill disabled");
			AVDebugWriteLine("Chill is disabled");
		}
	}

	void MainPage::slider_RadeonChill_Min_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Convert new value
		int newValue = (int)e.NewValue();

		//Set chill settings
		IADLX3DChillPtr d3dChill;
		res = d3dSettingSrv->GetChill(gpuInfo, &d3dChill);
		res = d3dChill->SetMinFPS(newValue);
		if (ADLX_FAILED(res))
		{
			//Set result
			textblock_RadeonChill_Min().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
			textblock_Status().Text(L"Failed setting chill fps");
			AVDebugWriteLine(L"Failed setting chill fps");
		}
		else
		{
			//Match values
			if (newValue > slider_RadeonChill_Max().Value())
			{
				slider_RadeonChill_Max().Value(newValue);
			}

			//Set result
			textblock_RadeonChill_Min().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
			textblock_Status().Text(L"Chill minimum set to " + number_to_wstring(newValue));
			AVDebugWriteLine(L"Chill minimum set to " << newValue);
		}
	}

	void MainPage::slider_RadeonChill_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Convert new value
		int newValue = (int)e.NewValue();

		//Set chill setting
		IADLX3DChillPtr d3dChill;
		res = d3dSettingSrv->GetChill(gpuInfo, &d3dChill);
		res = d3dChill->SetMaxFPS(newValue);
		if (ADLX_FAILED(res))
		{
			//Set result
			textblock_RadeonChill_Max().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
			textblock_Status().Text(L"Failed setting chill fps");
			AVDebugWriteLine(L"Failed setting chill fps");
		}
		else
		{
			//Match values
			if (newValue < slider_RadeonChill_Min().Value())
			{
				slider_RadeonChill_Min().Value(newValue);
			}

			//Set result
			textblock_RadeonChill_Max().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
			textblock_Status().Text(L"Chill maximum set to " + number_to_wstring(newValue));
			AVDebugWriteLine(L"Chill maximum set to " << newValue);
		}
	}
}