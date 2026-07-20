#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::DisplaySettings_Convert_ToUI_Current(DisplaySettings displaySettings)
	{
		try
		{
			//Display Color Enhancement
			if (displaySettings.ColorEnhancement.Current.has_value())
			{
				combobox_Display_DisplayColorEnhancement().SelectedIndex(displaySettings.ColorEnhancement.Current.value());
			}

			//Brightness
			if (displaySettings.Brightness.Current.has_value())
			{
				slider_Display_Brightness().Value(displaySettings.Brightness.Current.value());
			}

			//Contrast
			if (displaySettings.Contrast.Current.has_value())
			{
				slider_Display_Contrast().Value(displaySettings.Contrast.Current.value());
			}

			//Saturation
			if (displaySettings.Saturation.Current.has_value())
			{
				slider_Display_Saturation().Value(displaySettings.Saturation.Current.value());
			}

			//Hue
			if (displaySettings.Hue.Current.has_value())
			{
				slider_Display_Hue().Value(displaySettings.Hue.Current.value());
			}

			//Color Temperature Control
			if (displaySettings.ColorTemperatureControl.Current.has_value())
			{
				toggleswitch_Display_ColorTemperature_Control().IsOn(displaySettings.ColorTemperatureControl.Current.value());
			}

			//Color Temperature Kelvin
			if (displaySettings.ColorTemperatureKelvin.Current.has_value())
			{
				slider_Display_ColorTemperature_Kelvin().Value(displaySettings.ColorTemperatureKelvin.Current.value());
			}

			//Color Deficiency Correction Control
			if (displaySettings.CVDCControl.Current.has_value())
			{
				toggleswitch_Display_CVDC_Control().IsOn(displaySettings.CVDCControl.Current.value());
			}

			//Color Deficiency Correction Protanopia
			if (displaySettings.CVDCProtanopia.Current.has_value())
			{
				slider_Display_Protanopia().Value(displaySettings.CVDCProtanopia.Current.value());
			}

			//Color Deficiency Correction Deuteranopia
			if (displaySettings.CVDCDeuteranopia.Current.has_value())
			{
				slider_Display_Deuteranopia().Value(displaySettings.CVDCDeuteranopia.Current.value());
			}

			//Color Deficiency Correction Tritanopia
			if (displaySettings.CVDCTritanopia.Current.has_value())
			{
				slider_Display_Tritanopia().Value(displaySettings.CVDCTritanopia.Current.value());
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