#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlxValuesResetDisplay()
	{
		try
		{
			//Color Temperature
			slider_Display_ColorTemperature().Value(6500);

			//Brightness
			slider_Display_Brightness().Value(0);

			//Contrast
			slider_Display_Contrast().Value(100);

			//Saturation
			slider_Display_Saturation().Value(100);

			//Hue
			slider_Display_Hue().Value(0);

			//Return result
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed resetting display settings.");
			return false;
		}
	}
}