#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::DisplaySettings_Convert_ToUI_Profile(DisplaySettings displaySettings, AdlSettingGet settingType)
	{
		try
		{
			//FreeSync
			if (displaySettings.FreeSyncEnabled.Get(settingType).has_value())
			{
				toggleswitch_Display_FreeSync().IsOn(displaySettings.FreeSyncEnabled.Get(settingType).value());
			}

			//Display Color Enhancement
			if (displaySettings.ColorEnhancement.Get(settingType).has_value())
			{
				combobox_Display_DisplayColorEnhancement().SelectedIndex(displaySettings.ColorEnhancement.Get(settingType).value());
			}

			//Brightness
			if (displaySettings.Brightness.Get(settingType).has_value())
			{
				slider_Display_Brightness().Value(displaySettings.Brightness.Get(settingType).value());
			}

			//Contrast
			if (displaySettings.Contrast.Get(settingType).has_value())
			{
				slider_Display_Contrast().Value(displaySettings.Contrast.Get(settingType).value());
			}

			//Saturation
			if (displaySettings.Saturation.Get(settingType).has_value())
			{
				slider_Display_Saturation().Value(displaySettings.Saturation.Get(settingType).value());
			}

			//Hue
			if (displaySettings.Hue.Get(settingType).has_value())
			{
				slider_Display_Hue().Value(displaySettings.Hue.Get(settingType).value());
			}

			//Color Gamma Red
			if (displaySettings.GammaRed.Get(settingType).has_value())
			{
				slider_Display_GammaRed().Value(displaySettings.GammaRed.Get(settingType).value());
			}

			//Color Gamma Green
			if (displaySettings.GammaGreen.Get(settingType).has_value())
			{
				slider_Display_GammaGreen().Value(displaySettings.GammaGreen.Get(settingType).value());
			}

			//Color Gamma Blue
			if (displaySettings.GammaBlue.Get(settingType).has_value())
			{
				slider_Display_GammaBlue().Value(displaySettings.GammaBlue.Get(settingType).value());
			}

			//Color Temperature Control
			if (displaySettings.ColorTemperatureControl.Get(settingType).has_value())
			{
				toggleswitch_Display_ColorTemperature_Control().IsOn(displaySettings.ColorTemperatureControl.Get(settingType).value());
			}

			//Color Temperature Kelvin
			if (displaySettings.ColorTemperatureKelvin.Get(settingType).has_value())
			{
				slider_Display_ColorTemperature_Kelvin().Value(displaySettings.ColorTemperatureKelvin.Get(settingType).value());
			}

			//Color Deficiency Correction Control
			if (displaySettings.CVDCControl.Get(settingType).has_value())
			{
				toggleswitch_Display_CVDC_Control().IsOn(displaySettings.CVDCControl.Get(settingType).value());
			}

			//Color Deficiency Correction Protanopia
			if (displaySettings.CVDCProtanopia.Get(settingType).has_value())
			{
				slider_Display_Protanopia().Value(displaySettings.CVDCProtanopia.Get(settingType).value());
			}

			//Color Deficiency Correction Deuteranopia
			if (displaySettings.CVDCDeuteranopia.Get(settingType).has_value())
			{
				slider_Display_Deuteranopia().Value(displaySettings.CVDCDeuteranopia.Get(settingType).value());
			}

			//Color Deficiency Correction Tritanopia
			if (displaySettings.CVDCTritanopia.Get(settingType).has_value())
			{
				slider_Display_Tritanopia().Value(displaySettings.CVDCTritanopia.Get(settingType).value());
			}

			//Eyefinity Automatic
			if (displaySettings.EyefinityAutomatic.Get(settingType).has_value())
			{
				bool settingValue = displaySettings.EyefinityAutomatic.Get(settingType).value();
				toggleswitch_Eyefinity_Automatic().IsOn(settingValue);
				textblock_Eyefinity_Automatic_Value().Text(settingValue ? L"Enabled" : L"Disabled");
			}
			else
			{
				textblock_Eyefinity_Automatic_Value().Text(L"Disabled");
			}

			//Return result
			AVDebugWriteLine(L"Display settings applied to interface (Profile)");
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed applying display settings to interface (Profile)");
			return false;
		}
	}
}