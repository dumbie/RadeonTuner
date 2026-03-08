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
			//Brightness
			slider_Display_Brightness().Value(0);

			//Contrast
			slider_Display_Contrast().Value(100);

			//Saturation
			slider_Display_Saturation().Value(100);

			//Hue
			slider_Display_Hue().Value(0);

			//Color Temperature Control
			toggleswitch_Display_ColorTemperature_Control().IsOn(true);

			//Color Temperature Kelvin
			slider_Display_ColorTemperature_Kelvin().Value(6500);

			//Color Deficiency Correction Control
			toggleswitch_Display_CVDC_Control().IsOn(false);

			//Color Deficiency Correction Protanopia
			slider_Display_Protanopia().Value(0);

			//Color Deficiency Correction Deuteranopia
			slider_Display_Deuteranopia().Value(0);

			//Color Deficiency Correction Tritanopia
			slider_Display_Tritanopia().Value(0);

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