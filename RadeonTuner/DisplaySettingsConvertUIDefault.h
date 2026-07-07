#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::DisplaySettings_Convert_ToUI_Default(DisplaySettings displaySettings)
	{
		try
		{
			////HDR Enabled
			//if (displaySettings.HdrEnabled.Default.has_value())
			//{
			//	toggleswitch_HdrEnabled().IsOn(displaySettings.HdrEnabled.Default.value());
			//}

			//Brightness
			if (displaySettings.Brightness.Default.has_value())
			{
				slider_Display_Brightness().Value(displaySettings.Brightness.Default.value());
			}

			//Contrast
			if (displaySettings.Contrast.Default.has_value())
			{
				slider_Display_Contrast().Value(displaySettings.Contrast.Default.value());
			}

			//Saturation
			if (displaySettings.Saturation.Default.has_value())
			{
				slider_Display_Saturation().Value(displaySettings.Saturation.Default.value());
			}

			//Hue
			if (displaySettings.Hue.Default.has_value())
			{
				slider_Display_Hue().Value(displaySettings.Hue.Default.value());
			}

			//Color Temperature Control
			if (displaySettings.ColorTemperatureControl.Default.has_value())
			{
				toggleswitch_Display_ColorTemperature_Control().IsOn(displaySettings.ColorTemperatureControl.Default.value());
			}

			//Color Temperature Kelvin
			if (displaySettings.ColorTemperatureKelvin.Default.has_value())
			{
				slider_Display_ColorTemperature_Kelvin().Value(displaySettings.ColorTemperatureKelvin.Default.value());
			}

			//Color Deficiency Correction Control
			if (displaySettings.CVDCControl.Default.has_value())
			{
				toggleswitch_Display_CVDC_Control().IsOn(displaySettings.CVDCControl.Default.value());
			}

			//Color Deficiency Correction Protanopia
			if (displaySettings.CVDCProtanopia.Default.has_value())
			{
				slider_Display_Protanopia().Value(displaySettings.CVDCProtanopia.Default.value());
			}

			//Color Deficiency Correction Deuteranopia
			if (displaySettings.CVDCDeuteranopia.Default.has_value())
			{
				slider_Display_Deuteranopia().Value(displaySettings.CVDCDeuteranopia.Default.value());
			}

			//Color Deficiency Correction Tritanopia
			if (displaySettings.CVDCTritanopia.Default.has_value())
			{
				slider_Display_Tritanopia().Value(displaySettings.CVDCTritanopia.Default.value());
			}

			//Return result
			AVDebugWriteLine(L"Display settings applied to interface.");
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed applying display settings to interface.");
			return false;
		}
	}
}