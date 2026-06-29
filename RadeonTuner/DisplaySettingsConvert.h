#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::DisplaySettings_Convert_ToUI(DisplaySettings displaySettings)
	{
		try
		{
			//Brightness
			if (displaySettings.Brightness.has_value())
			{
				slider_Display_Brightness().Value(displaySettings.Brightness.value());
			}

			//Contrast
			if (displaySettings.Contrast.has_value())
			{
				slider_Display_Contrast().Value(displaySettings.Contrast.value());
			}

			//Saturation
			if (displaySettings.Saturation.has_value())
			{
				slider_Display_Saturation().Value(displaySettings.Saturation.value());
			}

			//Hue
			if (displaySettings.Hue.has_value())
			{
				slider_Display_Hue().Value(displaySettings.Hue.value());
			}

			//Color Temperature Control
			if (displaySettings.ColorTemperatureControl.has_value())
			{
				toggleswitch_Display_ColorTemperature_Control().IsOn(displaySettings.ColorTemperatureControl.value());
			}

			//Color Temperature Kelvin
			if (displaySettings.ColorTemperatureKelvin.has_value())
			{
				slider_Display_ColorTemperature_Kelvin().Value(displaySettings.ColorTemperatureKelvin.value());
			}

			//Color Deficiency Correction Control
			if (displaySettings.CVDCControl.has_value())
			{
				toggleswitch_Display_CVDC_Control().IsOn(displaySettings.CVDCControl.value());
			}

			//Color Deficiency Correction Protanopia
			if (displaySettings.CVDCProtanopia.has_value())
			{
				slider_Display_Protanopia().Value(displaySettings.CVDCProtanopia.value());
			}

			//Color Deficiency Correction Deuteranopia
			if (displaySettings.CVDCDeuteranopia.has_value())
			{
				slider_Display_Deuteranopia().Value(displaySettings.CVDCDeuteranopia.value());
			}

			//Color Deficiency Correction Tritanopia
			if (displaySettings.CVDCTritanopia.has_value())
			{
				slider_Display_Tritanopia().Value(displaySettings.CVDCTritanopia.value());
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

	std::optional<DisplaySettings> MainPage::DisplaySettings_Generate_FromUI()
	{
		try
		{
			DisplaySettings displaySettings{};

			//Brightness
			if (slider_Display_Brightness().IsEnabled())
			{
				displaySettings.Brightness = slider_Display_Brightness().Value();
			}

			//Contrast
			if (slider_Display_Contrast().IsEnabled())
			{
				displaySettings.Contrast = slider_Display_Contrast().Value();
			}

			//Saturation
			if (slider_Display_Saturation().IsEnabled())
			{
				displaySettings.Saturation = slider_Display_Saturation().Value();
			}

			//Hue
			if (slider_Display_Hue().IsEnabled())
			{
				displaySettings.Hue = slider_Display_Hue().Value();
			}

			//Color Temperature Control
			if (toggleswitch_Display_ColorTemperature_Control().IsEnabled())
			{
				displaySettings.ColorTemperatureControl = toggleswitch_Display_ColorTemperature_Control().IsOn();
			}

			//Color Temperature Kelvin
			if (slider_Display_ColorTemperature_Kelvin().IsEnabled())
			{
				displaySettings.ColorTemperatureKelvin = slider_Display_ColorTemperature_Kelvin().Value();
			}

			//Color Deficiency Correction Control
			if (toggleswitch_Display_CVDC_Control().IsEnabled())
			{
				displaySettings.CVDCControl = toggleswitch_Display_CVDC_Control().IsOn();
			}

			//Color Deficiency Correction Protanopia
			if (slider_Display_Protanopia().IsEnabled())
			{
				displaySettings.CVDCProtanopia = slider_Display_Protanopia().Value();
			}

			//Color Deficiency Correction Deuteranopia
			if (slider_Display_Deuteranopia().IsEnabled())
			{
				displaySettings.CVDCDeuteranopia = slider_Display_Deuteranopia().Value();
			}

			//Color Deficiency Correction Tritanopia
			if (slider_Display_Tritanopia().IsEnabled())
			{
				displaySettings.CVDCTritanopia = slider_Display_Tritanopia().Value();
			}

			//Return result
			return displaySettings;
		}
		catch (...)
		{
			//Return result
			return std::nullopt;
		}
	}
}