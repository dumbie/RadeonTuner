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
			//HDR Enabled
			if (displaySettings.HdrEnabled.Get(settingType).has_value())
			{
				toggleswitch_Display_HdrEnabled().IsOn(displaySettings.HdrEnabled.Get(settingType).value());
			}

			//FreeSync Mode
			if (displaySettings.FreeSyncMode.Get(settingType).has_value())
			{
				combobox_Display_FreeSyncMode().SelectedIndex(displaySettings.FreeSyncMode.Get(settingType).value());
			}

			//Virtual Super Resolution
			if (displaySettings.VsrEnabled.Get(settingType).has_value())
			{
				toggleswitch_Display_VSR().IsOn(displaySettings.VsrEnabled.Get(settingType).value());
			}

			//Gpu Scaling
			if (displaySettings.GpuScalingEnabled.Get(settingType).has_value())
			{
				toggleswitch_Display_GpuScaling().IsOn(displaySettings.GpuScalingEnabled.Get(settingType).value());
			}

			//Integer Scaling
			if (displaySettings.IntegerScalingEnabled.Get(settingType).has_value())
			{
				toggleswitch_Display_IntegerScaling().IsOn(displaySettings.IntegerScalingEnabled.Get(settingType).value());
			}

			//Scaling Mode
			if (displaySettings.ScalingMode.Get(settingType).has_value())
			{
				combobox_Display_ScalingMode().SelectedIndex(displaySettings.ScalingMode.Get(settingType).value());
			}

			//Color Depth
			if (displaySettings.ColorDepth.Get(settingType).has_value())
			{
				combobox_Display_ColorDepth().SelectedIndex(displaySettings.ColorDepth.Get(settingType).value());
			}

			//Pixel Format
			if (displaySettings.PixelFormat.Get(settingType).has_value())
			{
				combobox_Display_PixelFormat().SelectedIndex(displaySettings.PixelFormat.Get(settingType).value());
			}

			//Color Enhancement
			if (displaySettings.ColorEnhancement.Get(settingType).has_value())
			{
				combobox_Display_DisplayColorEnhancement().SelectedIndex(displaySettings.ColorEnhancement.Get(settingType).value());
			}

			//Color Temperature Control
			if (displaySettings.ColorTemperatureControl.Get(settingType).has_value())
			{
				toggleswitch_Display_ColorTemperature_Control().IsOn(displaySettings.ColorTemperatureControl.Get(settingType).value());
				slider_Display_ColorTemperature_Kelvin().IsEnabled(displaySettings.ColorTemperatureControl.Get(settingType).value());
			}

			//Color Temperature Kelvin
			if (displaySettings.ColorTemperatureKelvin.Get(settingType).has_value())
			{
				slider_Display_ColorTemperature_Kelvin().Value(displaySettings.ColorTemperatureKelvin.Get(settingType).value());
			}

			//Color Brightness
			if (displaySettings.Brightness.Get(settingType).has_value())
			{
				slider_Display_Brightness().Value(displaySettings.Brightness.Get(settingType).value());
			}

			//Color Contrast
			if (displaySettings.Contrast.Get(settingType).has_value())
			{
				slider_Display_Contrast().Value(displaySettings.Contrast.Get(settingType).value());
			}

			//Color Saturation
			if (displaySettings.Saturation.Get(settingType).has_value())
			{
				slider_Display_Saturation().Value(displaySettings.Saturation.Get(settingType).value());
			}

			//Color Hue
			if (displaySettings.Hue.Get(settingType).has_value())
			{
				slider_Display_Hue().Value(displaySettings.Hue.Get(settingType).value());
			}

			//Color Deficiency Correction Control
			if (displaySettings.CVDCControl.Get(settingType).has_value())
			{
				toggleswitch_Display_CVDC_Control().IsOn(displaySettings.CVDCControl.Get(settingType).value());
				slider_Display_Protanopia().IsEnabled(displaySettings.CVDCControl.Get(settingType).value());
				slider_Display_Deuteranopia().IsEnabled(displaySettings.CVDCControl.Get(settingType).value());
				slider_Display_Tritanopia().IsEnabled(displaySettings.CVDCControl.Get(settingType).value());
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

			//Vari-Bright Enabled
			if (displaySettings.VariBrightEnabled.Get(settingType).has_value())
			{
				toggleswitch_Display_VariBright().IsOn(displaySettings.VariBrightEnabled.Get(settingType).value());
				combobox_Display_VariBright_Level().IsEnabled(displaySettings.VariBrightEnabled.Get(settingType).value());
			}

			//Vari-Bright Level
			if (displaySettings.VariBrightLevel.Get(settingType).has_value())
			{
				combobox_Display_VariBright_Level().SelectedIndex(displaySettings.VariBrightLevel.Get(settingType).value());
			}

			//HDCP Support
			if (displaySettings.HDCPEnabled.Get(settingType).has_value())
			{
				toggleswitch_Display_HDCPSupport().IsOn(displaySettings.HDCPEnabled.Get(settingType).value());
			}

			//Automatic Eyefinity
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